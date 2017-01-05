//
//  QBSettings.h
//  Core
//

//  Copyright 2011 QuickBlox team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Quickblox/QBNullability.h>
#import <Quickblox/QBGeneric.h>
#import "QBLogger.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, QBConnectionZoneType) {
    
    QBConnectionZoneTypeAutomatic       = 1, //Default. Endpoints are loaded from QuickBlox
    QBConnectionZoneTypeProduction      = 2,
    QBConnectionZoneTypeDevelopment     = 3,
    QBConnectionZoneTypeStage           = 4
};

/** 
 *  QBSettings class interface.
 *  Class for framework setup.
 */
@interface QBSettings : NSObject

/**
 *  Allows to set api endpoint and chat endpoint for service zone.
 *
 *  @note QBConnectionZoneTypeAutomatic is used by default.
 *  If you are using shared server and you are migrating to enterprise account,
 *  then you don't need to resubmit your application, endpoints will be updated automatically.
 
 *  To set custom endpoints use QBConnectionZoneTypeProduction or QBConnectionZoneTypeDevelopment service zone.
 *  Then you should manually activate your service zone by calling setServiceZone:
 *
 *  @param apiEndpoint  apiEndpoint - Endpoint for service i.e. http://my_custom_endpoint.com. Possible to pass nil to return to default settings
 *  @param chatEndpoint chat endpoint
 *  @param zone         QBConnectionZoneType - service zone
 */
+ (void)setApiEndpoint:(nullable NSString *)apiEndpoint chatEndpoint:(nullable NSString *)chatEndpoint forServiceZone:(QBConnectionZoneType)zone;

#pragma mark -
#pragma mark Chat settings

/**
 *  Enable or disable chat auto reconnect
 *
 *  @param autoReconnectEnabled The default value is NO
 */
+ (void)setAutoReconnectEnabled:(BOOL)autoReconnectEnabled;

/**
 *  Enable or disable message carbons
 *
 *  @note Call this method after chat connection has been established
 *  @param carbonsEnabled BOOL value
 */
+ (void)setCarbonsEnabled:(BOOL)carbonsEnabled;

/// Set timeout value for Stream Management send a message operation
+ (void)setStreamManagementSendMessageTimeout:(NSUInteger)streamManagementSendMessageTimeout;

/** A reconnect timer may optionally be used to attempt a reconnect periodically.
    Default value is 5 seconds */
+ (void)setReconnectTimerInterval:(NSTimeInterval)reconnectTimerInterval;

/**
 * Many routers will teardown a socket mapping if there is no activity on the socket.
 * For this reason, the stream supports sending keep-alive data.
 * This is simply whitespace, which is ignored by the protocol.
 *
 * Keep-alive data is only sent in the absence of any other data being sent/received.
 *
 * The default value is 20s.
 * The minimum value for TARGET_OS_IPHONE is 10s, else 20s.
 *
 * To disable keep-alive, set the interval to zero (or any non-positive number).
 *
 * The keep-alive timer (if enabled) fires every (keepAliveInterval / 4) seconds.
 * Upon firing it checks when data was last sent/received,
 * and sends keep-alive data if the elapsed time has exceeded the keepAliveInterval.
 * Thus the effective resolution of the keepalive timer is based on the interval.
 */
+ (void)setKeepAliveInterval:(NSTimeInterval)keepAliveInterval;

#pragma mark -
#pragma mark Credentials

/// Storing Application ID
+ (void)setApplicationID:(NSUInteger)applicationID;

/**
 Set account key
 
 @param accountKey Account key - from admin.quickblox.com
 */
+ (void)setAccountKey:(NSString *)accountKey;

/**
 * Setting API Key for Quickblox API
 *
 * @param authKey - NSString value of API Key.
 */
+ (void)setAuthKey:(NSString *)authKey;

/**
 * Setting API Secret for Quickblox API
 *
 * @param authSecret - NSString value of API Secret.
 */
+ (void)setAuthSecret:(NSString *)authSecret;

/**
 * Setting application group identifier
 *
 * @param appGroupIdentifier - NSString value of identifier.
 */

+ (void)setApplicationGroupIdentifier:(NSString *)appGroupIdentifier;

#pragma mark -
#pragma mark Endpoints

/**
 * Allows to change Services Zone to work with Production, Development and Staging environments
 *
 * @param serviceZone - Service Zone. One from QBConnectionZoneType. Default - QBConnectionZoneTypeAutomatic.
 */
+ (void)setServiceZone:(QBConnectionZoneType)serviceZone;

/**
 *  Return current Service Zone
 *
 *  @note serviceZone - Service Zone. One from QBConnectionZoneType. Default - QBConnectionZoneTypeAutomatic
 */
+ (QBConnectionZoneType)currentServiceZone;

/**
 *  Returns Api Endpoint for current zone
 *
 *  @return NSString value of Api Endpoint
 */
+ (nullable NSString *)apiEndpoint;

#pragma mark -
#pragma mark Chat Endpoints

/**
 Get server's Chat endpoint

 @note you have to prepend http or https prefix
 @return Current server's Chat endpoint
 */
+ (NSString *)chatEndpoint;

#pragma mark -
#pragma mark Network Indicator

/**
 * A Boolean value indicating whether the manager is enabled.
 
 * If YES, the manager will change status bar network activity indicator according to network operation notifications it receives.
 * The default value is NO.
 */
+ (void)setNetworkIndicatorManagerEnabled:(BOOL)enabled;

/**
 A Boolean value indicating whether the network activity indicator is currently displayed in the status bar.
 */
+ (BOOL)isNetworkIndicatorVisible;

#pragma mark -
#pragma mark Logging

/**
 Set SDK log level (by default: QBLogLevelDebug). Possible values: QBLogLevelDebug, QBLogLevelNothing.
 
 @param logLevel New log level
 */
+ (void)setLogLevel:(QBLogLevel)logLevel;

/**
 *  Enable full XMPP Framework logging to console. By default is disabled.
 */
+ (void)enableXMPPLogging;

/**
 *  Enable log to file
 *  The approximate maximum size to allow log files to grow.
 *  If a log file is larger than this value after a log statement is appended,
 *  then the log file is rolled.
 *  @param maximumFileSize maximum file size in bytes, for example: 1024 * 1024 * 10 = 10Mb
 */
+ (void)enableFileLoggingWithMaximumFileSize:(unsigned long long)maximumFileSize;

/**
 *  Disable logging to file
 */
+ (void)disableFileLogging;

/**
 *  Returns log file paths if loggint to file is enabled
 *  Example name of log file: /var/mobile/Containers/Data/Application/518F9FD2-BB4C-4AF4-89D8-7FF85B0518B7/Library/Caches/Logs/com.quickblox.supersample 2016-03-25 11-23.log
 *
 *  @return Array of log file paths or nil if logging to file is disabled
 */
+ (nullable NSArray<NSString *> *)logFilePaths;

/**
 *   Disable full XMPP Framework logging to console.
 */
+ (void)disableXMPPLogging;

#pragma mark - 
#pragma mark NSURLSessionConfiguration

/**
 *  Set custom session configuration that will be used for REST API requests.
 *  '[NSURLSessionConfiguration defaultSessionConfiguration]' is used if nil is passed.
 *
 *  @param configuration Your NSURLSessionConfiguration object.
 */
+ (void)setSessionConfiguration:(nullable NSURLSessionConfiguration *)configuration;

/**
 *  Get custom session configuration.
 *
 *  @return Your NSURLSessionConfiguration object.
 */
+ (nullable NSURLSessionConfiguration *)sessionConfiguration;

#pragma mark - DEPRECATED

/**
 *  Enable or Disable chat DNS Lookup cache for current chat endpoint
 *
 *  Caches DNS lookup for chat api endpoint.
 *
 *  @param enable YES / NO. Defaults NO
 *
 *  @warning *Deprecated in 2.7.6.*
 */
+ (void)setChatDNSLookupCacheEnabled:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("Deprecated in 2.7.6. This feature was removed.");

/**
 *  Get Chat DNS lookup cache enabled state
 *
 *  @warning *Deprecated in 2.7.6.*
 *
 *  @return YES if cache is enabled, NO if cache is disabled.
 */
+ (BOOL)isChatDNSLookupCacheEnabled DEPRECATED_MSG_ATTRIBUTE("Deprecated in 2.7.6. This feature was removed.");

/**
 *  Enable or disable Stream Resumption (XEP-0198).
 *
 *  @param streamResumptionEnabled BOOL value. The default value is NO
 */
+ (void)setStreamResumptionEnabled:(BOOL)streamResumptionEnabled DEPRECATED_MSG_ATTRIBUTE("Deprecated in 2.7.6. This feature was removed.");

@end

NS_ASSUME_NONNULL_END
