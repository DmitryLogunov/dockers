#include "lib/server_http.hpp"

// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#include "workers/api.hpp"

#ifdef HAVE_OPENSSL
#include "lib/crypto.hpp"
#endif

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main() {

  HttpServer server;
  server.config.port = 8888;

   // GET-example for the path /api/action
  // Responds with request-information
  server.resource["^/api/factorial/([0-9]+)$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    unsigned int input_number = (unsigned int)stoi(request->path_match[1]);
    response->write(Api::factorial(input_number));
  };

  // GET-example for the path /match/[number], responds with the matched string in path (number)
  // For instance a request GET /match/123 will receive: 123
  server.resource["^/match/([0-9]+)$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    response->write(request->path_match[1]);
  };

  // GET-example simulating heavy work in a separate thread
  server.resource["^/work$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> /*request*/) {
    thread work_thread([response] {
      this_thread::sleep_for(chrono::seconds(5));
      response->write("Work done");
    });
    work_thread.detach();
  };

  server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
    // Handle errors here
    // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
  };

  thread server_thread([&server]() {
    // Start server
    server.start();
  });

  // Wait for server to start so that the client can connect
  this_thread::sleep_for(chrono::seconds(1));

  server_thread.join();
}

