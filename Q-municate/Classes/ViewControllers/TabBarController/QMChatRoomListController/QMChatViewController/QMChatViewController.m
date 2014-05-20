//
//  QMChatViewController.m
//  Q-municate
//
//  Created by Igor Alefirenko on 01/04/2014.
//  Copyright (c) 2014 Quickblox. All rights reserved.
//

#import "QMChatViewController.h"
#import "QMChatViewCell.h"
#import "QMChatDataSource.h"
#import "QMContactList.h"
#import "QMChatService.h"
#import "QMUtilities.h"

static CGFloat const kCellHeightOffset = 33.0f;

@interface QMChatViewController ()

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet UIView *inputMessageView;
@property (weak, nonatomic) IBOutlet UITextField *inputMessageTextField;
@property (nonatomic, strong) QMChatDataSource *dataSource;
@property (assign) BOOL isBackButtonClicked;

@property (nonatomic, strong) NSMutableArray *chatHistory;

@end

@implementation QMChatViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.title = self.chatName;
    
    [self configureInputMessageViewShadow];
    [self addKeyboardObserver];
	[self addChatObserver];
	self.isBackButtonClicked = NO;
    
    // update unread message count:
    [self updateChatDialog];

    // retrieve chat history:
    self.chatHistory = [QMChatService shared].allConversations[self.chatDialog.ID];
    if (self.chatHistory == nil) {
        
#warning fix it!
        if ([self.chatDialog.occupantIDs count] == 1) {    // created now:
            NSMutableArray *emptyHistory = [NSMutableArray new];
            [QMChatService shared].allConversations[self.chatDialog.ID] = emptyHistory;
            [self resetTableView];
            return;
        }
        
        // fetch chat history from server:
        [QMUtilities createIndicatorView];
        [[QMChatService shared] getMessageHistoryWithDialogID:self.chatDialog.ID withCompletion:^(NSArray *chatDialogHistoryArray, NSError *error) {
            [QMUtilities removeIndicatorView];
            if (chatDialogHistoryArray != nil) {
                [QMChatService shared].allConversations[self.chatDialog.ID] = chatDialogHistoryArray;
            }
            [self resetTableView];
        }];
    }
}

- (void)updateChatDialog
{
    self.chatDialog.unreadMessageCount = 0;
}

- (void)dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)addChatObserver
{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(localChatDidNotSendMessage:) name:kChatDidNotSendMessage object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(localChatDidReceiveMessage:) name:kChatDidReceiveMessage object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(localChatDidFailWithError:) name:kChatDidFailWithError object:nil];
}

- (void)configureNavBarButtons
{
	BOOL isGroupChat = YES;

	if (isGroupChat) {
		UIButton *groupInfoButton = [UIButton buttonWithType:UIButtonTypeCustom];
		[groupInfoButton setFrame:CGRectMake(0, 0, 30, 40)];

		[groupInfoButton setImage:[UIImage imageNamed:@"ic_info_top"] forState:UIControlStateNormal];
		[groupInfoButton setImage:[UIImage imageNamed:@"ic_info_top"] forState:UIControlStateHighlighted];
		[groupInfoButton addTarget:self action:@selector(groupInfoNavButtonAction) forControlEvents:UIControlEventTouchUpInside];
		UIBarButtonItem *groupInfoBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:groupInfoButton];
		self.navigationItem.rightBarButtonItems = @[groupInfoBarButtonItem];
	} else {
		UIButton *videoButton = [UIButton buttonWithType:UIButtonTypeCustom];
		UIButton *audioButton = [UIButton buttonWithType:UIButtonTypeCustom];
		[videoButton setFrame:CGRectMake(0, 0, 30, 40)];
		[audioButton setFrame:CGRectMake(0, 0, 30, 40)];

		[videoButton setImage:[UIImage imageNamed:@"ic_camera_top"] forState:UIControlStateNormal];
		[videoButton setImage:[UIImage imageNamed:@"ic_camera_top"] forState:UIControlStateHighlighted];
		[videoButton addTarget:self action:@selector(videoCallAction) forControlEvents:UIControlEventTouchUpInside];

		[audioButton setImage:[UIImage imageNamed:@"ic_phone_top"] forState:UIControlStateNormal];
		[audioButton setImage:[UIImage imageNamed:@"ic_phone_top"] forState:UIControlStateHighlighted];
		[audioButton addTarget:self action:@selector(audioCallAction) forControlEvents:UIControlEventTouchUpInside];

		UIBarButtonItem *videoCallBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:videoButton];
		UIBarButtonItem *audioCallBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:audioButton];
		self.navigationItem.rightBarButtonItems = @[audioCallBarButtonItem, videoCallBarButtonItem];
	}
}


- (void)addKeyboardObserver
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(resizeViewWithKeyboardNotification:) name:UIKeyboardWillHideNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(resizeViewWithKeyboardNotification:) name:UIKeyboardWillShowNotification object:nil];
}

- (void)configureInputMessageViewShadow
{
    self.inputMessageView.layer.shadowColor = [UIColor darkGrayColor].CGColor;
    self.inputMessageView.layer.shadowOffset = CGSizeMake(0, -1.0);
    self.inputMessageView.layer.shadowOpacity = 0.5;
    self.inputMessageView.layer.shadowPath = [UIBezierPath bezierPathWithRect:[self.inputMessageView bounds]].CGPath;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)back:(id)sender
{
	self.isBackButtonClicked = YES;
	[self.navigationController popViewControllerAnimated:YES];
}


#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.chatHistory count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    QMChatViewCell *cell = (QMChatViewCell *)[tableView dequeueReusableCellWithIdentifier:kChatViewCellIdentifier];
    QBChatAbstractMessage *message = self.chatHistory[indexPath.row];
    
    QBUUser *currentUser = nil;
    if ([QMContactList shared].me.ID == message.senderID) {
        currentUser = [QMContactList shared].me;
    } else {
        currentUser = [[QMContactList shared] findFriendWithID:message.senderID];
    }
    [cell configureCellWithMessage:message fromUser:currentUser];

    return cell;
}

// height for cell:
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    QBChatAbstractMessage *chatMessage = self.chatHistory[indexPath.row];
    return [QMChatViewCell cellHeightForMessage:chatMessage.text] + kCellHeightOffset;
}

- (void)resetTableView
{
    self.chatHistory = [QMChatService shared].allConversations[self.chatDialog.ID];
    [self.tableView reloadData];
}

#pragma mark - Keyboard
- (void)clearMessageInputTextField
{
	self.inputMessageTextField.text = kEmptyString;
	[self.inputMessageTextField resignFirstResponder];
}
- (void)resizeViewWithKeyboardNotification:(NSNotification *)notification
{
	if (self.isBackButtonClicked) {
		[self clearMessageInputTextField];
	} else {
		/*
		* below code is to follow animation of keyboard
		* for view with textField and buttons('send', 'transfer')
		* but still need to count tabBar height and time for animation
		* */
		NSDictionary * userInfo = notification.userInfo;
		NSTimeInterval animationDuration;
		UIViewAnimationCurve animationCurve;
		CGRect keyboardFrame;
		[[userInfo valueForKey:UIKeyboardAnimationCurveUserInfoKey] getValue:&animationCurve];
		[[userInfo valueForKey:UIKeyboardAnimationDurationUserInfoKey] getValue:&animationDuration];
		[[userInfo valueForKey:UIKeyboardFrameEndUserInfoKey] getValue:&keyboardFrame];

		BOOL isKeyboardShow = !(keyboardFrame.origin.y == [[UIScreen mainScreen] bounds].size.height);

		NSInteger keyboardHeight = isKeyboardShow ? - keyboardFrame.size.height +49.0f: keyboardFrame.size.height -49.0f;

		[UIView animateWithDuration:animationDuration delay:0.0f options:animationCurve << 16 animations:^
		{
			CGRect frame = self.view.frame;
			frame.size.height += keyboardHeight;
			self.view.frame = frame;

			[self.view layoutIfNeeded];

		} completion:nil];
	}
}

#pragma mark - Nav Buttons Actions
- (void)audioCallAction
{
	//
}

- (void)videoCallAction
{
	//
}

- (void)groupInfoNavButtonAction
{
	//
}

#pragma mark - Chat Notifications
- (void)localChatDidNotSendMessage:(NSNotification *)notification
{
	NSLog(@"userInfo: %@", notification.userInfo);
//	[self showAlertWithErrorMessage:notification.userInfo];
	[QMUtilities removeIndicatorView];
}

- (void)localChatDidReceiveMessage:(NSNotification *)notification
{
    [self resetTableView];
}

- (void)localChatDidFailWithError:(NSNotification *)notification
{
	NSLog(@"userInfo: %@", notification.userInfo);
	NSString *errorMessage;
	int errorCode = [notification.userInfo[@"errorCode"] integerValue];
	if (!errorCode) {
		errorMessage = @"QBChatServiceErrorConnectionRefused";
	} else if (errorCode == 1) {
		errorMessage = @"QBChatServiceErrorConnectionClosed";
	} else if (errorCode == 2) {
		errorMessage = @"QBChatServiceErrorConnectionTimeout";
	}
	[self showAlertWithErrorMessage:[NSString stringWithFormat:@"error: %@", errorMessage]];
}


#pragma mark -
- (IBAction)sendMessageButtonClicked:(UIButton *)sender
{
	if (self.inputMessageTextField.text.length) {
		QBChatMessage *chatMessage = [QBChatMessage new];
		chatMessage.text = self.inputMessageTextField.text;
		chatMessage.senderID = [QMContactList shared].me.ID;
        
		if (self.chatDialog.type == QBChatDialogTypePrivate) { // private chat
            chatMessage.recipientID = self.opponent.ID;
			[[QMChatService shared] sendMessage:chatMessage];

		} else { // group chat
			if ([self.chatDialog.occupantIDs count] > 1) {
				[[QMChatService shared] postMessage:chatMessage withRoom:[QMChatService shared].chatRoom withCompletion:^(QBChatDialog *dialog, NSError *error) {
					//
				}];
			}
		}
        self.inputMessageTextField.text = @"";
        [self resetTableView];
	}
}

- (void)addMessageToHistory:(QBChatMessage *)chatMessage
{
	[self.dataSource addMessageToHistory:chatMessage];
	[self clearMessageInputTextField];
	[self.tableView reloadData];
}

#pragma mark -
- (void)showAlertWithErrorMessage:(NSString *)messageString
{
	[[[UIAlertView alloc] initWithTitle:kAlertTitleErrorString message:messageString delegate:self cancelButtonTitle:kAlertButtonTitleOkString otherButtonTitles:nil] show];
}

@end