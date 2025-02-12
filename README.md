# stormserver
StormServer http(s) server

# Build
```
git clone --recursive https://github.com/mikelsv/stormserver.git
git clone https://github.com/mikelsv/msvcore2.git

MSVS 20122: stormserver/stormserver.vcxproj
GCC: stormserver/Makefile
```

# Configure
`Listen [ip:]port` Listen port

`DirectoryIndex index.html index.php index.msl` Set directory index files

`DocumentRoot /home/www/all` Set default document root

`AccessLog logs/access.log` Set default access log

`FullLog logs/fullog.log` Set default full log

`RewriteEngine on` Enable pcre

`RewriteRule setup setup.html [L]` Use rule. See Apache examples.

Extension CGI
```
Extension cgi{
UseType php
Execute /usr/bin/php-cgi
}
```

Enable modstate. Use: yousite.com/stormserver-modstate
```
ModState On
ModStateRule stormserver-modstate
```

# Virtual servers:
```
VirtualHost{
# Server name in Host request
ServerName domain.com
ServerName www.domain.com
ServerName 192.168.1.1

# Document root
DocumentRoot /home/www/domain.com/

# Replace domain.com/id1234567 -> domain.com/id.php?_user_id=1234567
RewriteRule ^id([-A-Za-z0-9_'%]+)$ id.php?_user_id=$1 [L,SQA]

# Use as proxy
ProxyRequests On
ProxyPass / http://domain-next.com/

# Logs
AccessLog logs/domain.com-access.log
FullLog logs/domain.com-fullog.log
}
```

# SSL
```
SSLHost *:443{
# Enable SSL
SSLEngine on

# Sertificates
SSLCertificateFile ./cert/domain.com.pem
SSLCertificateKeyFile ./cert/domain.com.key

# Use ServerName, DocumentRoot, AccessLog ant other optins
}
```
