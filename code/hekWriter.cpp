#include "hekWriter.h"

void hekWriter::write_data() {
    // for each char in data stream
        // add char encoding into buffer string
            // IF buffer length >= 8:
            // right strip and write to file

    // while buffer length != 0 && length > 8
        // right strip and write to file

    // if buffer length != 0 && lengt < 8
        // add padding according to protocol
        // update padding_byte
            // zeros for the padding; ones for the encoding

}
