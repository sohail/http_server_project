# May Allah help us all.

try:
    import httpheaders
        
    content = "POST /api/messages HTTP/1.1\r\nAuthorization: Bearer\r\nContent-Type: application/json; charset=utf-8\r\nContent-Length: 88\r\nHost: localhost:3978\r\n\r\n<html>\r\n<head>\r\n<title>Hi!</title>\r\n</head>\r\n<body>\r\n<p>Hi friend.</p>\r\n</body>\r\n</html>"

    httpheaders_obj = httpheaders.httpheaders(content, len(content))

    # Tries to print message body
    print (httpheaders_obj)

    print ("\n<!----------------------------------------------------------------/>")

    for l in httpheaders_obj:        
        print (str (l[0]) + ":" + str (l[1]))

    print ("<!----------------------------------------------------------------/>")

    print (httpheaders_obj("METHOD"))
    print (httpheaders_obj("RESOURCE"))
    print (httpheaders_obj("VERSION"))
    print (httpheaders_obj("Content-Length"))
    print (httpheaders_obj("VERSION"))
    if httpheaders_obj("VERSION") == bytes("HTTP/1.1", 'utf-8'):
        print ("We found it")
    else:
        print ("not found")        

    print ("<!----------------------------------------------------------------/>")

    #TODO
    #print (str (httpheaders_obj))

except (ImportError, MemoryError, TypeError) as e:
   print (e)        


