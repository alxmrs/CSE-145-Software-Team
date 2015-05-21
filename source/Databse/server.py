'''
CSE 145 EEG Server

@author Alex Rosengarten
@date May 19 2015

Function: This listens for a remote procedure call from a seizure classifier. If the classifier detects a seizure, this server will save up to the last hour of EEG/EKG data in to a SQLite database.

'''


#imports
import db_api as db

import socket
import sys
import json
from jsonrpc import JSONRPCResponseManager, dispatcher



@dispatcher.add_method
def foo(name):
    name = name + 1
    return "Hello, {}".format(name)


HOST = '0.0.0.0' # 0.0.0.0 ==> listen on all interfaces
PORT = 8888

# AF_INET/SOCK_STREAM - type of socket, these are the most standard
#IPV4 TCP socket
# Address Family Internet, Socket Stream (type of socket)
#datagram = UDP, stream = symetric of communication
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
    s.bind((HOST, PORT))
except s.err as msg:
    print 'Bind failed. Error Code: ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()

print 'Socket bind complete'

s.listen(5) # starts listening to incoming connections
print 'Socket now listening'


try:
    while True:
        conn, addr = s.accept() # grab the next person from the queue
        # conn is another socket, addr is the address of person connected to sever
        print "Connected with " + addr[0] + " : " + str(addr[1])

        while True:
            incoming_msg = conn.recv(1024)
            # conn.sendall("recieved")

            print incoming_msg

            response = JSONRPCResponseManager.handle(incoming_msg, dispatcher)
            conn.sendall(response.json)

except KeyboardInterrupt:
    print("Shutting down cleanly...")
    s.close()



'''
    {"method": "foo", "params": ["echome!"], "jsonrpc": "2.0", "id": 0}

'''

'''
def processJSON(self, request):
    try:
        json_obj = json.loads(request)
    except ValueError, e:
        raise ValueError('Bad JSON: {}'.format(e))

    try:
        method = json_obj['method']
        params = json_obj['params']
        id     = json_obj['id']
    except KeyError, e:
        raise ValueError("JSON body missing parameter: {}".format(e))

    if not isinstance(params, list):
        raise ValueError("Bad params %r: must be a list" % params)

    try:
        method = getattr(self.obj, method) # raises AttributeError
    except AttributeError:
        raise ValueError("No such method {}".format(method))

    try:
        result = method(*params)
    except:
        tb = traceback.format_exc)
        exc_value = sys.exc_info()[1]
        error_value = dict(
            name='JSONRPCError',
            code=100,
            message=str(exc_value),
            error=tb)
        return json.dumps(dict(result=None, error=error_value, id=id))
    # create response object of type JSON to be returned
    response = json.dumps(dict(result=result, error=None, id=id))
    return response
'''




# create the socket
'''
class mysocket:

    def __init__(self, sock=None):
        if sock is None:
            # Create a new socket
            self.sock = socket.socket(
                socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.sock = sock

    def connect(self, host, port):
        self.sock.connect((host,port))

    def mysend(self, msg):
        totalsent = 0
        MSGLEN = len(msg)
        while totalsent < MSGLEN:
            sent = self.sock.send(msg[totalsent:])
            if sent == 0:
                raise RuntimeError("socket connection broken")
            totalsent = totalsent + sent

    def myreceive(self):
        chunks = []
        bytes_recd = 0
        while bytes_recd < MSGLEN:
            chunk = self.sock.recv(min(MSGLEN - bytes_recd, 2048))

            if chunk == '':
                raise RuntimeError("socket connection broken")
            chunks.append(chunk)
            bytes_recd = bytes_recd + len(chunk)
        return ''.join(chunks)

        '''