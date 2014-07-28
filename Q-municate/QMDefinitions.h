//
//  QMDefinitions.h
//  Q-municate
//
//  Created by Igor Alefirenko on 14/02/2014.
//  Copyright (c) 2014 Quickblox. All rights reserved.
//

#ifndef Q_municate_Definitions_h
#define Q_municate_Definitions_h

#define IS_HEIGHT_GTE_568 [[UIScreen mainScreen ] bounds].size.height == 568.0f
#define $(...)  [NSSet setWithObjects:__VA_ARGS__, nil]

#define CHECK_OVERRIDE()\
@throw\
[NSException exceptionWithName:NSInternalInconsistencyException \
reason:[NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)]\
userInfo:nil]

/*QMContentService*/
typedef void(^QMContentProgressBlock)(float progress);
typedef void(^QMCFileUploadTaskResultBlockBlock)(QBCFileUploadTaskResult *result);
typedef void(^QMCFileDownloadTaskResultBlockBlock)(QBCFileDownloadTaskResult *result);

typedef void (^QBUUserResultBlock)(QBUUserResult *result);
typedef void (^QBAAuthResultBlock)(QBAAuthResult *result);
typedef void (^QBUUserLogInResultBlock)(QBUUserLogInResult *result);
typedef void (^QBAAuthSessionCreationResultBlock)(QBAAuthSessionCreationResult *result);
typedef void (^QBUUserPagedResultBlock)(QBUUserPagedResult *pagedResult);
typedef void (^QBMRegisterSubscriptionTaskResultBlock)(QBMRegisterSubscriptionTaskResult *result);
typedef void (^QBMUnregisterSubscriptionTaskResultBlock)(QBMUnregisterSubscriptionTaskResult *result);
typedef void (^QBDialogsPagedResultBlock)(QBDialogsPagedResult *result);
typedef void (^QBChatDialogResultBlock)(QBChatDialogResult *result);
typedef void (^QBChatHistoryMessageResultBlock)(QBChatHistoryMessageResult *result);

typedef void (^QBResultBlock)(Result *result);
typedef void (^QBSessionCreationBlock)(BOOL success, NSString *error);
typedef void (^QBChatResultBlock)(BOOL success);
typedef void (^QBChatRoomResultBlock)(QBChatRoom *chatRoom, NSError *error);
typedef void (^QBChatDialogHistoryBlock)(NSMutableArray *chatDialogHistoryArray, NSError *error);

//************** Segue Identifiers *************************
static NSString *const kTabBarSegueIdnetifier         = @"TabBarSegue";
static NSString *const kSplashSegueIdentifier         = @"SplashSegue";
static NSString *const kWelcomeScreenSegueIdentifier  = @"WelcomeScreenSegue";
static NSString *const kSignUpSegueIdentifier         = @"SignUpSegue";
static NSString *const kLogInSegueSegueIdentifier     = @"LogInSegue";
static NSString *const kDetailsSegueIdentifier        = @"DetailsSegue";
static NSString *const kVideoCallSegueIdentifier      = @"VideoCallSegue";
static NSString *const kAudioCallSegueIdentifier      = @"AudioCallSegue";
static NSString *const kStartAudioCallSegueIdentifier = @"StartAudioCallSegue";
static NSString *const kStartVideoCallSegueIdentifier = @"StartVideoCallSegue";
static NSString *const kChatViewSegueIdentifier       = @"ChatViewSegue";
static NSString *const kIncomingCallIdentifier        = @"IncomingCallIdentifier";
static NSString *const kProfileSegueIdentifier        = @"ProfileSegue";
static NSString *const kCreateNewChatSegueIdentifier  = @"CreateNewChatSegue";
static NSString *const kContentPreviewSegueIdentifier = @"ContentPreviewIdentifier";
static NSString *const kGroupDetailsSegueIdentifier   = @"GroupDetailsSegue";

//****************** Cell Identifiers  ********************
static NSString *const kSettingsVCCellIdentifier                = @"SettingsCellIdentifier";

static NSString *const kChatUploadingAttachmentCellIdentitier   = @"UploadingAttachIdentifier";
static NSString *const kChatInvitationCellIdentifier            = @"InvitationCell";
static NSString *const kChatPrivateContentCellIdentifier        = @"PrivateContentCell";
static NSString *const kChatPrivateMessageCellIdentifier        = @"PrivateChatCell";
static NSString *const kChatGroupContentCellIdentifier          = @"GroupContentCell";

//**************** Setting Cell Titles ********************
static NSString *const kSettingsCellTitleProfile            = @"Profile";
static NSString *const kSettingsCellTitlePushNotifications  = @"Push Notifications";
static NSString *const kSettingsCellTitleChangePassword     = @"Change Password";
static NSString *const kSettingsCellBundleVersion           = @"CFBundleVersion";

//****************** Notifications  ***********************
static NSString *const kAllUsersLoadedNotification    = @"All users loaded";
static NSString *const kLoggedInNotification          = @"LoggedInNotification";

static NSString *const kChatDidNotSendMessageNotification               = @"ChatDidNotSendMessageNotification";
static NSString *const kChatDidReceiveMessageNotification               = @"ChatDidReceiveMessageNotification";
static NSString *const kChatDidFailWithErrorNotification                = @"ChatDidFailWithErrorNotification";
static NSString *const kChatDidSendMessageNotification                  = @"ChatDidSendMessageNotification";
static NSString *const kChatRoomDidEnterNotification                    = @"ChatRoomDidEnterNotification";
static NSString *const kChatRoomDidReceiveMessageNotification           = @"ChatRoomDidReceiveMessageNotification";
static NSString *const kChatDialogsDidLoadedNotification                = @"ChatDialogsDidLoadedNotification";
static NSString *const kChatRoomDidChangeOnlineUsersListNotification    = @"ChatRoomDidChangeOnlineUsersListNotification";

static NSString *const kChatRoomListUpdateNotification	= @"kChatRoomListUpdateNotification";
static NSString *const kInviteFriendsDataSourceShouldRefreshNotification 	 = @"kInviteFriendsDataSourceShouldRefreshNotification";

static NSString *const kChatDialogUpdatedNotification = @"ChatDialogUpdated";


//****************** Calls Notifications  ***********************
static NSString *const kIncomingCallNotification = @"Incoming Call";
static NSString *const kCallWasStoppedNotification = @"Call was stopped";
static NSString *const kCallWasRejectedNotification = @"Call Was Rejected";
static NSString *const kCallUserDidNotAnswerNotification = @"User didn't answer";
static NSString *const kCallDidAcceptByUserNotification = @"User accepted call";
static NSString *const kCallDidStartedByUserNotification = @"Call was started";


static NSString *const kChatViewCellIdentifier          = @"ChatViewCell";
static NSString *const kCreateChatCellIdentifier        = @"CreateChatCell";
static NSString *const kGroupDetailsCellIdentifier      = @"GroupDetailsCell";
static NSString *const kContactListCellIdentifier       = @"contactsCell";
static NSString *const kFacebookCellIdentifier          = @"facebookCell";
static NSString *const kInviteFriendCellIdentifier      = @"InviteFriendCell";


static NSString *const kUserIsBusyStatus            = @"User is busy";
static NSString *const kUserDoesntAnswerStatus      = @"User doesn't answer";

static NSString *const kCallBadConnectionStatus     = @"Bad connection";
static NSString *const kCallWasStoppedByUserStatus  = @"Call was stopped";
static NSString *const kCallConnectingStatus        = @"Connecting...";


//******************** USER DEFAULTS KEYS *****************

static NSString *const kFacebook    = @"facebook";

static NSString *const kFriendId               = @"FriendID";
static NSString *const kUserDataInfoDictionary = @"QBUserObject";

static NSString *const kEmptyString                     = @"";

static NSString *const kTableHeaderFriendsString        = @"Friends";
static NSString *const kTableHeaderAllUsersString       = @"All Users";

static NSString *const kFacebookFriendStatus            = @"Facebook friend";
static NSString *const kAddressBookUserStatus           = @"Contact List";

static NSString *const kMessageString                   = @"Input email please.";
static NSString *const kMoreResultString                = @"For more results:";
static NSString *const kSearchingFriendsString          = @"You have no friends yet. Try to search for new friends";
static NSString *const kNoChatString                    = @"No Chat yet";
static NSString *const kStatusOnlineString              = @"Online";
static NSString *const kStatusOfflineString             = @"Offline";

static NSString *const kMailSubjectString               = @"Q-municate";
static NSString *const kMailBodyString                  = @"<a href='http://quickblox.com/'>Join us in Q-municate!</a>";
static NSString *const kButtonTitleDoneString           = @"Done";
static NSString *const kButtonTitleSaveString           = @"Save";

static NSString *const kErrorKeyFromDictionaryString    	= @"error";

static NSString *const kAlertTitleErrorString               = @"Error";
static NSString *const kAlertTitleSuccessString             = @"Success";
static NSString *const kAlertTitleInProgressString          = @"In Progress";
static NSString *const kAlertTitleEnterPasswordString       = @"Enter password:";
static NSString *const kAlertTitleAreYouSureString          = @"Are you sure?";
static NSString *const kAlertTitlePasswordIsShortString     = @"Password is too short";
static NSString *const kAlertTitleEnterNewPasswordString    = @"Enter new Password";
static NSString *const kAlertTitleConfirmNewPasswordString      = @"Confirm Password";
static NSString *const kAlertTitleChangingStatusString      = @"Changing status:";

static NSString *const kAlertBodyWrongPasswordString            = @"Wrong password";
static NSString *const kAlertBodyPasswDoesNotMatchString        = @"Passwords don't match";
static NSString *const kAlertBodyPasswordIsShortString          = @"Password is too short";
static NSString *const kAlertBodyPasswordChangedString          = @"Password changed";
static NSString *const kAlertBodyFillInAllFieldsString          = @"Fill in all the fields";
static NSString *const kAlertBodyMessageWasSentToMailString     = @"Message was sent to your email. Check it";
static NSString *const kAlertBodyRecordPostedString             = @"Invitation was posted to wall.";
static NSString *const kAlertBodyRecordSentViaMailString        = @"Invitation was sent via email.";
static NSString *const kAlertBodyNoContactsWithEmailsString     = @"No contacts with emails";
static NSString *const kAlertBodySetUpYourEmailClientString     = @"Please, set up your email client";
static NSString *const kAlertButtonTitleOkString        = @"OK";
static NSString *const kAlertButtonTitleHackItString    = @"Hack it!";
static NSString *const kAlertButtonTitleCancelString    = @"Cancel";
static NSString *const kAlertButtonTitleLogOutString    = @"Log Out";

static NSString *const kButtonTitleCreatePrivateChatString 	= @"Create Private Chat";
static NSString *const kButtonTitleCreateGroupChatString 	= @"Create Group Chat";

static NSString *const kSettingsProfileDefaultStatusString	= @"Add Status";
static NSString *const kSettingsProfileMessageWarningString	= @"This field could not be empty!";
static NSString *const kSettingsProfileTextViewMessageWarningString	= @"This field could not be more then 43 characters!";




#endif
