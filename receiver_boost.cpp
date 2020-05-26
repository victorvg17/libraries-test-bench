#include <fstream>
#include <iostream>
#include <sstream>
#include <zmq.hpp>
#include "gps_position.hpp"

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/////////////////////////////////////////////////////////////
// gps coordinate
//
// illustrates serialization for a simple type
//
using namespace std;

int main() {
	// ... some time later restore the class instance to its orginal state
    gps_position newg;

    //set the zmq part
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    const string& topic = "22 serialization";
    socket.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());

    socket.connect("tcp://localhost:5031");
    zmq::message_t request;

    while(1) {
    	// cout << "inside receive while" << endl;
    	socket.recv(&request);

    	const string cl_data(static_cast<char*>(request.data()), request.size());
    	/*
    	// create and open an archive for input
    	
	    std::istringstream istr_s(cl_data);
	    // boost::archive::text_iarchive ia(ifs);
	    boost::archive::text_iarchive ia(istr_s);
	    // read class state from archive
	    ia >> newg;
	    */
	    newg.deserialize_from_string(cl_data);
	    // archive and stream closed when destructors are called
	    cout << "receiving string: " << cl_data <<" with size: "<< cl_data.size() << endl;

	    // cout << "received deg: " << newg.gps_get_degrees()
	    //         << " received min: " << newg.gps_get_minutes()
	    //         << " received sec: " << newg.gps_get_seconds() << endl;
        newg.print_class_data();
        
    }
    
    
    return 0;
}