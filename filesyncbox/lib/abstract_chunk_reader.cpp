#include "filesyncbox/abstract_chunk_reader.h"

void abstract_chunk_reader::read_chunk(byte_array const& ohash)
{
    byte_array data = store::read_stores(ohash);
    if (!data.is_empty())
        return got_data(ohash, data);

    // Request asynchronously from other nodes
    chunk_share::request_chunk(this, ohash);
}

