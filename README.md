# http\_server\_project
A frame work to build an HTTP server. Written by, sqm@hackers.pk

The http\_headers\_src folder has C source code of "httpheaders" module. The module is used to parse HTTP request/reply. An example application **http-serv.py** is part of this repository. Please use this application to know the smarts of the "httpheaders" module. 

The _example application_ uses another CPython module **argsv-cpython** to parse command line arguments you can colne it from here... github.com/sohail/argsv.git 

___Example Application___

```
import httpheaders

content = "POST /api/messages HTTP/1.1\r\nAuthorization: Bearer\r\nContent-Type: application/json; charset=utf-8\r\nContent-Length: 88\r\nHost: localhost:3978\r\n\r\n<html>\r\n<head>\r\n<title>Hi!</title>\r\n</head>\r\n<body>\r\n<p>Hi friend.</p>\r\n</body>\r\n</html>"

httpheaders\_obj = httpheaders.httpheaders(content, len(content))

for l in httpheaders\_obj:
    print l[0] + ": " + l[1]

print str(httpheaders\_obj)
```

