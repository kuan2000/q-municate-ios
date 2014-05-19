//
//  QMChatService.h
//  Q-municate
//
//  Created by Igor Alefirenko on 17/02/2014.
//  Copyright (c) 2014 Quickblox. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface QMChatService : NSObject

@property (strong, nonatomic) QBWebRTCVideoChat *activeStream;

@property (strong, nonatomic) NSString *currentSessionID;
@property (nonatomic, strong) NSDictionary *customParams;
@property (nonatomic, strong) QBChatRoom *chatRoom;

+ (instancetype)shared;

// Log In & Log Out
- (void)loginWithUser:(QBUUser *)user completion:(QBChatResultBlock)block;
- (void)logOut;


#pragma mark - Audio/Video Chat

- (void)initActiveStream;                                                                           // for audio calls
- (void)initActiveStreamWithOpponentView:(UIView *)opponentView ownView:(UIView *)ownView;          // for video calls
- (void)releaseActiveStream;

- (void)postMessage:(QBChatMessage *)message;

- (void)createRoomWithName:(NSString *)groupChatNameString withCompletion:(QBChatRoomResultBlock)block;

- (void)createNewDialog:(QBChatDialog *)chatDialog withCompletion:(QBChatDialogResultBlock)block;

- (void)getMessageHistoryWithDialogID:(NSString *)dialogIDString withCompletion:(QBChatDialogHistoryBlock)block;

- (void)postMessage:(QBChatMessage *)chatMessage withRoom:(QBChatRoom *)chatRoom withCompletion:(QBChatDialogResultBlock)block;

- (void)callUser:(NSUInteger)userID withVideo:(BOOL)videoEnabled;

- (void)acceptCallFromUser:(NSUInteger)userID withVideo:(BOOL)videoEnabled customParams:(NSDictionary *)customParameters;
- (void)rejectCallFromUser:(NSUInteger)userID;

- (void)cancelCall;
- (void)finishCall;

@end
