//
//  QBChat.h
//  Chat
//
//  Copyright 2013 QuickBlox team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

/**
 QBChatServiceError enum defines following connection error codes:
 QBChatServiceErrorConnectionRefused - Connection with server is not available
 QBChatServiceErrorConnectionClosed  - Chat service suddenly became unavailable
 QBChatServiceErrorConnectionTimeout - Connection with server timed out
 */
typedef enum QBChatServiceError {
    QBChatServiceErrorConnectionRefused,
    QBChatServiceErrorConnectionClosed,
    QBChatServiceErrorConnectionTimeout
} QBChatServiceError;

/** QBChat class declaration. */
/** Overview */
/** This class is the main entry point to work with Quickblox Chat API. */

@interface QBChat : NSObject{
@private
    id<QBChatDelegate> delegate;
    QBUUser *qbUser;
}

/** QBChat delegate for callbacks */
@property (nonatomic, retain) id<QBChatDelegate> delegate;

/** Contact list */
@property (nonatomic, readonly) QBContactList *contactList;


#pragma mark -
#pragma mark Base Messaging

/**
 Get QBChat singleton
 
 @return QBChat Chat service singleton
 */
+ (QBChat *)instance;

/**
 Authorize on QuickBlox Chat
 
 @param user QBUUser structure represents user's login. Required user's fields: ID, password;
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)loginWithUser:(QBUUser *)user;

/**
 Check if current user logged into Chat
 
 @return YES if user is logged in, NO otherwise
 */
- (BOOL)isLoggedIn;

/**
 Logout current user from Chat
 
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)logout;

/**
 Send message
 
 @param message QBChatMessage structure which contains message text and recipient id
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)sendMessage:(QBChatMessage *)message;

/**
 Send presence message. Session will be closed in 90 seconds since last activity.
 
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)sendPresence;

/**
 Send presence message with status. Session will be closed in 90 seconds since last activity.
 
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)sendPresenceWithStatus:(NSString *)status;

/**
 Send direct presence message with status to user. User must be in your contact list.
 
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)sendDirectPresenceWithStatus:(NSString *)status toUser:(NSUInteger)userID;

/**
 Get current chat user
 
 @return An instance of QBUUser
 */
- (QBUUser *)currentUser;


#pragma mark -
#pragma mark Contact list

/**
 Add user to contact list request
 
 @param userID ID of user which you would like to add to contact list
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)addUserToContactListRequest:(NSUInteger)userID;

/**
 Remove user from contact list
 
 @param userID ID of user which you would like to remove from contact list
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)removeUserFromContactList:(NSUInteger)userID;

/**
 Confirm add to contact list request
 
 @param userID ID of user from which you would like to confirm add to contact request
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)confirmAddContactRequest:(NSUInteger)userID;

/**
 Reject add to contact list request
 
 @param userID ID of user from which you would like to reject add to contact request
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)rejectAddContactRequest:(NSUInteger)userID;


#pragma mark -
#pragma mark Rooms

/**
 Create room or join if room with this name already exist. QBChatDelegate's method 'chatRoomDidEnter:' will be called.
 If room name contains (" ") (space) character - it will be replaceed with "_" (underscore) character.
 If room name contains ("),(&),('),(/),(:),(<),(>),(@) (double quote, ampersand, single quote, forward slash, colon, less than, greater than, at-sign) characters - they will be removed.
 
 @param name Room name
 @param isMembersOnly YES if you want to create room that users cannot enter without being on the member list. If set NO - room will be opened for all users
 @param isPersistent YES if you want to create room that is not destroyed if the last user exits. If set NO - room will be destroyed if the last user exits.
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)createOrJoinRoomWithName:(NSString *)name membersOnly:(BOOL)isMembersOnly persistent:(BOOL)isPersistent;

/**
 Join room. QBChatDelegate's method 'chatRoomDidEnter:' will be called
 
 @param room Room to join
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)joinRoom:(QBChatRoom *)room;

/**
 Leave joined room. QBChatDelegate's method 'chatRoomDidLeave:' will be called
 
 @param room Room to leave
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)leaveRoom:(QBChatRoom *)room;

/**
 Destroy room. You can destroy room only if you are room owner or added to only members room by its owner. QBChatDelegate's method 'chatRoomDidDestroy:' will be called
 
 @param room Room to destroy
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)destroyRoom:(QBChatRoom *)room;

/**
 Send message to room
 
 @param message Message body
 @param room Room to send message
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)sendMessage:(NSString *)message toRoom:(QBChatRoom *)room;

/**
 Send presence with parameters to room
 
 @param parameters Presence parameters
 @param room Room to send presence
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)sendPresenceWithParameters:(NSDictionary *)parameters toRoom:(QBChatRoom *)room;

/**
 Send request for getting list of public groups. QBChatDelegate's method 'chatDidReceiveListOfRooms:' will be called
 
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)requestAllRooms;

/**
 Send request for getting room information. QBChatDelegate's method 'chatRoomDidReceiveInformation:room:' will be called
 
 @param room Room, which information you need to retrieve
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)requestRoomInformation:(QBChatRoom *)room;

/**
 Request users who are able to join a room. QBChatDelegate's method 'chatRoomDidReceiveListOfUsers:room:' will be called
 
 @param room Room
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)requestRoomUsers:(QBChatRoom *)room;

/**
 Request users who are joined a room. QBChatDelegate's method 'chatRoomDidReceiveListOfOnlineUsers:room:' will be called
 
 @param room Room
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)requestRoomOnlineUsers:(QBChatRoom *)room;

/**
 Send request to adding users to room.
 
 @param usersIDs Array of users' IDs
 @param room Room in which users will be added
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)addUsers:(NSArray *)usersIDs toRoom:(QBChatRoom *)room;

/**
 Send request to remove users from room
 
 @param usersIDs Array of users' IDs
 @param room Room from which users will be removed
 @return YES if the request was sent successfully. If not - see log.
 */
- (BOOL)deleteUsers:(NSArray *)usersIDs fromRoom:(QBChatRoom *)room;


#pragma mark -
#pragma mark VideoChat

/**
 Create and register new video chat instance

 @return Autoreleased instance of QBVideoChat;
 */
- (QBVideoChat *)createAndRegisterVideoChatInstance;


/**
 Unregister video chat instance
 
 @param videoChat Instance of video chat
 */
- (void)unregisterVideoChatInstance:(QBVideoChat *)videoChat;


#pragma mark -
#pragma mark Deprecated

/**
 @warning *Deprecated in QB iOS SDK 1.5:* You have to use method '- (void)createOrJoinRoomWithName:(NSString *)name membersOnly:(BOOL)isMembersOnly persistent:(BOOL)isPersistent' with isMembersOnly=NO and isPersistent=NO params instead
 
 Create public room. QBChatDelegate's method 'chatRoomDidEnter:' will be called
 
 @param name Room name
 */
- (BOOL)createRoomWithName:(NSString *)name __attribute__((deprecated()));

/**
 @warning *Deprecated in QB iOS SDK 1.5:* You have to use method '- (void)createOrJoinRoomWithName:(NSString *)name membersOnly:(BOOL)isMembersOnly persistent:(BOOL)isPersistent' with isMembersOnly=YES and isPersistent=NO params instead
 
 Create private room (only members). QBChatDelegate's method 'chatRoomDidEnter:' will be called
 
 @param name Room name
 */
- (BOOL)createPrivateRoomWithName:(NSString *)name __attribute__((deprecated()));

@end
