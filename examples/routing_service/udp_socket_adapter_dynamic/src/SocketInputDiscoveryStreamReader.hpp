/*
 * (c) 2019 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the Software.  Licensee has the right to distribute object form
 * only for use with RTI products.  The Software is provided "as is", with no
 * warranty of any type, including any warranty for fitness for any purpose.
 * RTI is under no obligation to maintain or support the Software.  RTI shall
 * not be liable for any incidental or consequential damages arising out of the
 * use or inability to use the software.
 */

#ifndef SOCKETDISCOVERYSTREAMREADER_HPP
#define SOCKETDISCOVERYSTREAMREADER_HPP

#include <fstream>
#include <mutex>

#include <rti/routing/adapter/AdapterPlugin.hpp>
#include <rti/routing/adapter/DiscoveryStreamReader.hpp>

/**
 * This class implements a DiscoveryStreamReader, a special kind of StreamReader
 * that provide discovery information about the available streams and their
 * types.
 */

class SocketInputDiscoveryStreamReader
        : public rti::routing::adapter::DiscoveryStreamReader {
public:
    SocketInputDiscoveryStreamReader(
            const rti::routing::PropertySet &,
            rti::routing::adapter::StreamReaderListener
                    *input_stream_discovery_listener);

    void take(std::vector<rti::routing::StreamInfo *> &) final;

    void return_loan(std::vector<rti::routing::StreamInfo *> &) final;

    /**
     * @brief Custom operation defined to indicate disposing off an <input>
     * when the SocketStreamReader has finished reading from the socket.
     * The SocketInputDiscoveryStreamReader will then create a new
     * discovery sample indicating that the stream has been disposed.
     * This will cause the Routing Service to start tearing down the Routes
     * associated with <input> having the corresponding <registered_type_name>
     * and <stream_name>.
     *
     * @param stream_info \b in. Reference to a StreamInfo object which should
     * be used when creating a new StreamInfo sample with disposed set to true
     */
    void dispose(const rti::routing::StreamInfo &stream_info);

private:
    std::mutex data_samples_mutex_;
    std::vector<std::unique_ptr<rti::routing::StreamInfo>> data_samples_;
    rti::routing::adapter::StreamReaderListener
            *input_stream_discovery_listener_;
};

#endif
