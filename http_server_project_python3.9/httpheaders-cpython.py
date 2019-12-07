# May Allah help us all.

try:
    import httpheaders
        
    content = "POST /api/messages HTTP/1.1\r\nAuthorization: Bearer\r\nContent-Type: application/json; charset=utf-8\r\nContent-Length: 88\r\nHost: localhost:3978\r\n\r\n<html>\r\n<head>\r\n<title>Hi!</title>\r\n</head>\r\n<body>\r\n<p>Hi friend.</p>\r\n</body>\r\n</html>"

    # print (content)

    # print (len(content))

    httpheaders_obj = httpheaders.httpheaders(content, len(content))

    for l in httpheaders_obj:        
        print (str(l[0]) + ":" + str(l[1]))

    print ("<!----------------------------------------------------------------/>")

    print (str(httpheaders_obj("METHOD")))
    print (str(httpheaders_obj("RESOURCE")))
    print (str(httpheaders_obj("VERSION")))
    print (str(httpheaders_obj("Content-Length")))

    print ("<!----------------------------------------------------------------/>")

    print (str(httpheaders_obj))

except (ImportError, MemoryError, TypeError) as e:
   print (e)        


