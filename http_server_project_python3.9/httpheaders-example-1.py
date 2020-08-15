# May Allah help us all.

try:
    import httpheaders
        
    content = "POST /api/messages HTTP/1.1\r\nAuthorization: Bearer\r\nContent-Type: application/json; charset=utf-8\r\nContent-Length: 88\r\nHost: localhost:3978\r\n\r\n<html>\r\n<head>\r\n<title>Hi!</title>\r\n</head>\r\n<body>\r\n<p>Hi friend.</p>\r\n</body>\r\n</html>"

    httpheaders_obj = httpheaders.httpheaders(content, len(content))

    # Tries to print message body
    print (httpheaders_obj)
    print ("<!----------------------------------------------------------------/>")

    # l is for list
    for l in httpheaders_obj:        
        print (l[0] + ":" + l[1])
    print ("<!----------------------------------------------------------------/>")    

    # Single line such as this "POST /api/messages HTTP/1.1\r\n" made into three seperate dictionary items
    print (httpheaders_obj("METHOD"))
    print (httpheaders_obj("RESOURCE"))
    print (httpheaders_obj("VERSION"))
    
    # I don't know what this is needed but here it is
    if httpheaders_obj("VERSION") == "HTTP/1.1":
        print ("Found...")
    else:
        print ("Not found.")        
    print ("<!----------------------------------------------------------------/>")   

    # To get to the request/reply payload/resource. Little hack, handler of str() still does'nt work
    resource = content[len(content) - int(httpheaders_obj("Content-Length")):]
    print (resource)

except (ImportError, MemoryError, TypeError) as e:
   print (e)        


