#!/usr/bin/python -O

""" Allah, The ONE. The ONLY ONE. """

""" Example usage... C:\>./http-serv.py src 127.0.0.1 port 3978 """

import sys, socket, threading, datetime, signal

src=None
port=None
h=False
v=False

class ThreadClass(threading.Thread):
    def __init__(self, client_socket_obj, forign_socket, reply):
        threading.Thread.__init__(self)
        self.client_socket_obj = client_socket_obj
        self.forign_socket = forign_socket
        self.ip, self.port = forign_socket
        self.reply = reply
        self.request_raw = ""

    def run(self):
        now = datetime.datetime.now()
        print "Client(forign socket) [IP=%s, port=%s]. Request received@%s" %(self.ip, self.port, now)

        self.request_raw = self.client_socket_obj.recv(4096)
        httpheaders_obj = httpheaders.httpheaders(self.request_raw, len(self.request_raw))

        body = str(httpheaders_obj)
        # Check against None is mandatory
        if body != None:
            print body

        # print httpheaders_obj

        # httpheaders_obj.body()

        print "Method = %s, Resource = %s, Version = %s" %(httpheaders_obj("METHOD"), httpheaders_obj("RESOURCE"), httpheaders_obj("VERSION"))
        #print "------------------- Request -------------------"
        #print self.request_raw
        #print "-------------------   END   -------------------"

        for l in httpheaders_obj:
            #print l
            #print l[0] + ": " + httpheaders_obj(l[0])
            print l[0] + ": " + l[1]
        
        self.client_socket_obj.send(self.reply)
        self.client_socket_obj.close()

def help():
    print "Hold on, kitty."

def version():
    print "0.0.0"

def ctrl_c_handler(signum, frame):
    print sys.argv[0] + ", Terminated"    

def main():
    signal.signal(signal.SIGINT, ctrl_c_handler)
    print "Server(local socket) [IP=" + src[0] + ", port=" + port[0] + "]" 

    try:
        serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serversocket.bind((src[0], int(port[0])))
        # Our server is now listening 
        serversocket.listen(socket.SOMAXCONN)

        reply_file = open("http-responses/original-response-file", "r")
        reply = reply_file.read()
        reply_file.close()
        
        while 1:
            (client_socket_obj, forign_socket) = serversocket.accept()
            client_service_thread = ThreadClass(client_socket_obj, forign_socket, reply)
            client_service_thread.start()
    except(socket.error, socket.gaierror, TypeError, IOError, AttributeError), e:
        print e
        sys.exit(0)


if __name__ == "__main__":
    try:
        import argsv, httpheaders

        args=argsv.argsv(sys.argv, "?,--help#v,--version#src,--src#port,--port")

        for arg in args:
            if arg["--src"]:
                src=arg["--src"](1)[1:]
            elif arg["--port"]:
                port=arg["--port"](1)[1:]
            elif arg["?"]:
                h=True
                break
            elif arg["v"]:
                v=True
                break
       
        if v == True:
            version()
        elif src == None or port == None or h == True:
            help()
        else:
            sys.exit(main()) 
                         
    except (ImportError), e: 
        print e	   
	
