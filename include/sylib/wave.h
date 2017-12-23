#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace sylib
{

class Wave
{/*{{{*/
	public:

		struct RiffChunk
		{/*{{{*/
			char chunk_id[4];
			uint32_t chunk_size;
			char format[4];
		};/*}}}*/

		struct FormatChunk
		{/*{{{*/
			char chunk_id[4];
			uint32_t chunk_size;
			uint16_t audio_format;
			uint16_t num_channels;
			uint32_t sample_rate;
			uint32_t byte_rate;
			uint16_t block_align;
uint16_t bits_per_sample;
		};/*}}}*/

		struct DataChunk
		{/*{{{*/
			char chunk_id[4];
			uint32_t chunk_size;
			vector<int32_t> datas;
		};/*}}}*/

		Wave () {};
		Wave (string filename);
		void showInfo ();
		bool read (string filename);
		bool write (string filename);

		RiffChunk riff_chunk;
		FormatChunk format_chunk;
		DataChunk data_chunk;

	private:
		bool readChunk ();
		template<typename T> void readBin (T& data);
		bool writeChunk ();
		template<typename T> void writeBin (T& data);
		template<typename T> string charToString (T& data);
		int32_t dataToInt32 (int32_t data);
		ifstream ifs;
		ofstream ofs;
};/*}}}*/

}
