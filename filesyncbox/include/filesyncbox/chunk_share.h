//
// Part of Metta OS. Check http://atta-metta.net for latest version.
//
// Copyright 2007 - 2014, Stanislav Karchebnyy <berkus@atta-metta.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

/**
 * Single-instance class that handles chunk sharing in the social network.
 *
 * Updating a file tree is handled by simply sending a NewRoot message with the outerhash
 * of new tree root block, which in turn would contain a merkle tree of outerhashes
 * for sub-trees. These sub-trees are recursively requested and are either satisfied
 * from local storage or pulled from another node.
 */
class chunk_share : public peer_service, private chunk_protocol
{
    /**
     * Outstanding chunk requests
     */
    static std::map<peer_id, request*> requests;

    /**
     * Maintain a persistent chunk query stream for each of our peers.
     */
    static std::map<peer_id, chunk_peer*> peers;

private:
    chunk_share();

public:
    static chunk_share *instance();

    static inline void init() { (void)instance(); }

    static void request_chunk(abstract_chunk_reader *reader, byte_array const& ohash);

private:
    static chunk_peer *peer(peer_id const& hostid, bool create);

    /**
     * Check all peers for chunks they might be able to download.
     */
    static void check_peers();

    /**
     * Check a particular request to see if it can still be satisfied;
     * otherwise delete it and send no_data() to all requestors.
     */
    static void check_request(request *req);

private:
    void got_out_stream_connected(stream *stream);
    void got_out_stream_disconnected(stream *stream);
    void got_in_stream_connected(stream *stream);
};
