meson build
cd build
ninja

Start one producer, and 2 consumer instances.

Pause one consumer using ctrl+z

-> The other consumer doesn't receive data anymore, and producer eats 100% CPU.

```sh
~/Sources/OpcTest on  main [?] ❯ ./producer
[2021-05-03 15:34:58.808 (UTC+0200)] warn/server	AccessControl: Unconfigured AccessControl. Users have all permissions.
[2021-05-03 15:34:58.808 (UTC+0200)] info/server	AccessControl: Anonymous login is enabled
[2021-05-03 15:34:58.808 (UTC+0200)] warn/server	Username/Password configured, but no encrypting SecurityPolicy. This can leak credentials on the network.
[2021-05-03 15:34:58.808 (UTC+0200)] warn/userland	AcceptAll Certificate Verification. Any remote certificate will be accepted.
[2021-05-03 15:34:58.809 (UTC+0200)] info/network	TCP network layer listening on opc.tcp://lappc-p898-in2p3-fr:4840/
Send 10485760 bytes
Send 10485760 bytes
[2021-05-03 15:35:01.655 (UTC+0200)] info/network	Connection 5 | New connection over TCP from ::1
[2021-05-03 15:35:01.655 (UTC+0200)] info/channel	Connection 5 | SecureChannel 1 | SecureChannel opened with SecurityPolicy http://opcfoundation.org/UA/SecurityPolicy#None and a revised lifetime of 600.00s
[2021-05-03 15:35:01.656 (UTC+0200)] info/channel	Connection 5 | SecureChannel 1 | Session 5b3f858b-2527-01a5-dd0d-f0df2662d6ed created
[2021-05-03 15:35:01.657 (UTC+0200)] info/session	SecureChannel 1 | Session ns=1;g=5b3f858b-2527-01a5-dd0d-f0df2662d6ed | ActivateSession: Session activated
[2021-05-03 15:35:01.657 (UTC+0200)] info/session	SecureChannel 1 | Session ns=1;g=5b3f858b-2527-01a5-dd0d-f0df2662d6ed | Subscription 1 | Created the Subscription with a publishing interval of 500.00 ms
[2021-05-03 15:35:01.677 (UTC+0200)] info/session	SecureChannel 1 | Session ns=1;g=5b3f858b-2527-01a5-dd0d-f0df2662d6ed | Subscription 1 | MonitoredItem 1 | Created the MonitoredItem (Sampling Interval: 250.000000ms, Queue Size: 0)
Send 10485760 bytes
Send 10485760 bytes
Send 10485760 bytes
[2021-05-03 15:35:03.848 (UTC+0200)] info/network	Connection 6 | New connection over TCP from ::1
[2021-05-03 15:35:03.848 (UTC+0200)] info/channel	Connection 6 | SecureChannel 2 | SecureChannel opened with SecurityPolicy http://opcfoundation.org/UA/SecurityPolicy#None and a revised lifetime of 600.00s
[2021-05-03 15:35:03.849 (UTC+0200)] info/channel	Connection 6 | SecureChannel 2 | Session 2cde63ef-7b12-24d0-7367-b6bbad1a7107 created
[2021-05-03 15:35:03.849 (UTC+0200)] info/session	SecureChannel 2 | Session ns=1;g=2cde63ef-7b12-24d0-7367-b6bbad1a7107 | ActivateSession: Session activated
[2021-05-03 15:35:03.850 (UTC+0200)] info/session	SecureChannel 2 | Session ns=1;g=2cde63ef-7b12-24d0-7367-b6bbad1a7107 | Subscription 2 | Created the Subscription with a publishing interval of 500.00 ms
[2021-05-03 15:35:03.857 (UTC+0200)] info/session	SecureChannel 2 | Session ns=1;g=2cde63ef-7b12-24d0-7367-b6bbad1a7107 | Subscription 2 | MonitoredItem 1 | Created the MonitoredItem (Sampling Interval: 250.000000ms, Queue Size: 0)
Send 10485760 bytes
Send 10485760 bytes
Send 10485760 bytes
Send 10485760 bytes
```

```sh
Sources/OpcTest/build on  main [?] ❯ ./consumer
[2021-05-03 15:35:01.653 (UTC+0200)] warn/userland	AcceptAll Certificate Verification. Any remote certificate will be accepted.
[2021-05-03 15:35:01.656 (UTC+0200)] info/channel	Connection 3 | SecureChannel 1 | SecureChannel opened with SecurityPolicy http://opcfoundation.org/UA/SecurityPolicy#None and a revised lifetime of 600.00s
[2021-05-03 15:35:01.656 (UTC+0200)] info/client	Client Status: ChannelState: Open, SessionState: Closed, ConnectStatus: Good
[2021-05-03 15:35:01.656 (UTC+0200)] info/client	Selected Endpoint opc.tcp://localhost:4840/ with SecurityMode None and SecurityPolicy http://opcfoundation.org/UA/SecurityPolicy#None
[2021-05-03 15:35:01.656 (UTC+0200)] info/client	Selected UserTokenPolicy open62541-anonymous-policy with UserTokenType Anonymous and SecurityPolicy http://opcfoundation.org/UA/SecurityPolicy#None
[2021-05-03 15:35:01.657 (UTC+0200)] info/client	Client Status: ChannelState: Open, SessionState: Created, ConnectStatus: Good
[2021-05-03 15:35:01.657 (UTC+0200)] info/client	Client Status: ChannelState: Open, SessionState: Activated, ConnectStatus: Good
[1] Received 10485760 bytes
[2] Received 10485760 bytes
[3] Received 10485760 bytes
[4] Received 10485760 bytes
[5] Received 10485760 bytes
[6] Received 10485760 bytes
[7] Received 10485760 bytes
^Z
[1]+  Stoppé                 ./consumer
```

```sh
Sources/OpcTest/build on  main [?] ❯ ./consumer
[2021-05-03 15:35:03.846 (UTC+0200)] warn/userland	AcceptAll Certificate Verification. Any remote certificate will be accepted.
[2021-05-03 15:35:03.848 (UTC+0200)] info/channel	Connection 3 | SecureChannel 2 | SecureChannel opened with SecurityPolicy http://opcfoundation.org/UA/SecurityPolicy#None and a revised lifetime of 600.00s
[2021-05-03 15:35:03.848 (UTC+0200)] info/client	Client Status: ChannelState: Open, SessionState: Closed, ConnectStatus: Good
[2021-05-03 15:35:03.849 (UTC+0200)] info/client	Selected Endpoint opc.tcp://localhost:4840/ with SecurityMode None and SecurityPolicy http://opcfoundation.org/UA/SecurityPolicy#None
[2021-05-03 15:35:03.849 (UTC+0200)] info/client	Selected UserTokenPolicy open62541-anonymous-policy with UserTokenType Anonymous and SecurityPolicy http://opcfoundation.org/UA/SecurityPolicy#None
[2021-05-03 15:35:03.849 (UTC+0200)] info/client	Client Status: ChannelState: Open, SessionState: Created, ConnectStatus: Good
[2021-05-03 15:35:03.850 (UTC+0200)] info/client	Client Status: ChannelState: Open, SessionState: Activated, ConnectStatus: Good
[4] Received 10485760 bytes
[5] Received 10485760 bytes
[6] Received 10485760 bytes
[7] Received 10485760 bytes
[2021-05-03 15:35:17.429 (UTC+0200)] error/client	Inactivity for Subscription 2.
[2021-05-03 15:35:27.430 (UTC+0200)] error/client	Inactivity for Subscription 2.
[2021-05-03 15:35:37.430 (UTC+0200)] error/client	Inactivity for Subscription 2.
[2021-05-03 15:35:47.430 (UTC+0200)] error/client	Inactivity for Subscription 2.
```

```
~ via ⬢ v14.16.1 took 1m47s ❯ ps aux | grep producer
pacaud    265612 93.0  0.5  97052 95088 pts/6    R+   15:34   1:58 /home/pacaud/Sources/OpcTest/build/producer
```

open62541 compilation options:

```
-DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF -DCMAKE_BUILD_TYPE=RelWithDebInfo -DUA_NAMESPACE_ZERO=REDUCED -DOPEN62541_VERSION=v1.2 -DUA_ENABLE_DISCOVERY=ON -DUA_ENABLE_DISCOVERY_MULTICAST=ON -DUA_ENABLE_PUBSUB=ON -DUA_ENABLE_PUBSUB_FILE_CONFIG=ON -DUA_ARCH_REMOVE_FLAGS="-Werror" -DUA_MULTITHREADING=200 -UA_LOGLEVEL=100
```
