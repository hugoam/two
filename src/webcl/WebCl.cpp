#define ZMQ_STATIC

#include <stl/string.h>
#include <stl/set.h>
#include <stl/map.h>
#include <stl/algorithm.h>
#include <infra/Vector.h>
#include <infra/File.h>
#include <infra/StringOps.h>
#include <webcl/WebCl.h>

#include "zmq.hpp"
#include "zmq_addon.hpp"

#include <json11.hpp>

#include <stl/string.hpp>
#include <stl/vector.hpp>
#include <stl/unordered_set.hpp>
#include <stl/unordered_map.hpp>

#include <string_view>

#include <cstdio>
#include <cassert>
#include <cstring>

namespace two
{
    using Json = json11::Json;
}

using namespace two;

int main(int argc, char *argv[])
{
    UNUSED(argc); UNUSED(argv);

#if 0
    int rc;

    // Set-up our context and sockets
    void* ctx = zmq_ctx_new();
    assert(ctx);

    // Start our server listening
    void* server = zmq_socket(ctx, ZMQ_STREAM);

    int notify = 0;
    zmq_setsockopt(server, ZMQ_STREAM_NOTIFY, &notify, sizeof(notify));

    zmq_bind(server, "tcp://*:8080");
    assert(server);

    while (1)
    {
        // Get HTTP request;
        // first frame has ID, the next the request.
        uint8_t id[256];
        int id_size = zmq_recv(server, id, 256, 0);
        assert(id_size > 0);

        // Get HTTP request
        char request[1024] = {};
        int size = zmq_recv(server, request, 1024, 0);
        printf("%s\n", request); // Professional Logging(TM)

        // define the response
        char http_response[] =
            "HTTP/1.0 200 OK\n"
            "Content-Type: text/html\n"
            "\n"
            "Hello, World!\n";

        // start sending response
        rc = zmq_send(server, id, id_size, ZMQ_SNDMORE);
        assert(rc != -1);
        // Send the http response
        rc = zmq_send(server,
            http_response,
            sizeof(http_response),
            ZMQ_SNDMORE
        );
        assert(rc != -1);

        // Send a zero to close connection to client
        rc = zmq_send(server, id, id_size, ZMQ_SNDMORE);
        assert(rc != -1);
        rc = zmq_send(server, NULL, 0, ZMQ_SNDMORE);
        assert(rc != -1);
    }

    rc = zmq_close(server);
    assert(rc == 0);

    rc = zmq_ctx_term(ctx);
    assert(rc == 0);

    return 0;
#else
    zmq::context_t ctx;

    zmq::socket_t stream(ctx, ZMQ_STREAM);
    stream.setsockopt(ZMQ_STREAM_NOTIFY, 0);

    stream.bind("tcp://*:8080");

    "POST / HTTP/1.1 200";
    "Content-Type: application/json";

    "{";
    "    sources: [";
    "        {";
    "            name: 'main.cpp'";
    "            content: '";
    "            '";
    "    ]";
    "}";

    auto process_request = [](const stl::string& request)
    {
        size_t separator = request.find("\r\n\r\n");
        if(separator == stl::string::npos)
            separator = request.find("\n\n");

        stl::string header = request.substr(0, separator);
        stl::string body = request.substr(separator + 1, stl::string::npos);

        if (!header.find("Content-Type: application/json"))
        {
            printf("[ERROR] Wrong content type - expected 'application/json'\n");
            return;
        }

        std::string errors;
        Json json = Json::parse(body.c_str(), errors);

        if (!errors.empty())
        {
            printf("[ERROR] Errors while parsing JSON\n");
            return;
        }

        stl::string project_path = "/home/hugoam/two/src/webproject";

        Json sources = json["sources"];

        for (const Json& source : sources.array_items())
        {
            stl::string name = source["name"].string_value().c_str();
            stl::string content = source["content"].string_value().c_str();

            write_file(project_path + "/" + name, content);
        }

        if (system(nullptr))
        {
            stl::string command = "cd /home/hugoam/two/build/projects/gmake/linux-clang/ && make config=releaseemscripten webproject";
            system(command.c_str());
        }
    };

    while (true) {

        //  Get HTTP request
        zmq::message_t sections[2] = {};
 
        const auto ret = zmq::recv_multipart(stream, sections);
        if (!ret)
            return 1;

        zmq::message_t frame = std::move(sections[0]);
        zmq::message_t body = std::move(sections[1]);

        stl::string request(body.data<char>(), body.size());

        printf("request(size=%d):\n%s\n", int(body.size()), request.c_str());
        process_request(request);

        //  Send Hello World response

        zmq::const_buffer send_msgs[2] = {
            zmq::const_buffer(frame.data(), frame.size()),
            zmq::str_buffer(
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "\r\n"
                "Hello, World!"
            )
        };
        if (!zmq::send_multipart(stream, send_msgs))
            return 1;

        // Close connection to browser
        zmq::const_buffer close_msgs[2] = {
            zmq::const_buffer(frame.data(), frame.size()),
            zmq::const_buffer()
        };
        zmq::send_multipart(stream, close_msgs);
    }

    return 0;
#endif
}
