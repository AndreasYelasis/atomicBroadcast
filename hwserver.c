//
//  Hello World server
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void)
{
    void *context = zmq_ctx_new ();

    //  Socket to talk to clients
    void *responder = zmq_socket (context, ZMQ_REP);
    zmq_bind (responder, "tcp://*:5555");

    while (1) {
        //  Wait for next request from client
        zmq_msg_t request;	// structure of the message. Never initialize the same zmq_msg_t twice.
        zmq_msg_init (&request); // Shall initialise the message object referenced. Return zero if successful.
        zmq_msg_recv (&request, responder, 0); // Receive a message part from the socket referenced by the socket argument and store it in the message referenced by the msg
        printf ("Received Hello\n");
        zmq_msg_close (&request); // Any resources associated with the message object referenced by msg are no longer required and may be released.

        //  Do some 'work'
        sleep (1);

        //  Send reply back to client
        zmq_msg_t reply;
        zmq_msg_init_size (&reply, 5);
        memcpy (zmq_msg_data (&reply), "World", 5);
        zmq_msg_send (&reply, responder, 0);
        //printf("Send reply %p\n",&reply);
        zmq_msg_close (&reply);
    }
    //  We never get here but if we did, this would be how we end
    zmq_close (responder);
    zmq_ctx_destroy (context);
    return 0;
}
