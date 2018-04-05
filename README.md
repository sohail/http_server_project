# http\_server\_project
A frame work to build an HTTP server. Written by, sqm@hackers.pk

The http\_headers\_src folder has C source code of "httpheaders" module. The module is used to parse HTTP request/reply. An example application **http-serv.py** is part of this repository. Please use this application to know the smarts of the "httpheaders" module. 

The _example application_ uses another CPython module **argsv-cpython** to parse command line arguments you can colne it from here... github.com/sohail/argsv.git 

___Example Application___
'code()'
import httpheaders

content = "POST /api/messages HTTP/1.1\r\nAuthorization: Bearer\r\nContent-Type: application/json; charset=utf-8\r\nContent-Length: 88\r\nHost: localhost:3978\r\n\r\n&lt;html&gt;\r\n&lt;head&gt;\r\n&lt;title&gt;Hi!&lt;/title&gt;\r\n&lt;/head&gt;\r\n&lt;body&gt;\r\n&lt;p&gt;Hi friend.&lt;/p&gt;\r\n&lt;/body&gt;\r\n&lt;/html&gt;"

httpheaders\_obj = httpheaders.httpheaders(content, len(content))

for l in httpheaders\_obj:
    print l[0] + ": " + l[1]

print str(httpheaders\_obj)

