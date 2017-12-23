#include <sylib/wave.h>
#include <typeinfo>
#include <string>

using namespace sylib;

void Wave::showInfo ()
{/*{{{*/
	cout<<"########## Riff Chunk ##########"<<endl;
	cout<<"chunk_id         : "<<charToString(riff_chunk.chunk_id)<<endl;
	cout<<"chunk_size       : "<<riff_chunk.chunk_size<<endl;
	cout<<"chunk_format     : "<<charToString(riff_chunk.format)<<endl;
	cout<<"########## Format Chunk ##########"<<endl;
	cout<<"chunk_id         : "<<charToString(format_chunk.chunk_id)<<" (must be \"fmt \")"<<endl;
	cout<<"chunk_size       : "<<format_chunk.chunk_size<<endl;
	cout<<"audio_format     : "<<format_chunk.audio_format<<endl;
	cout<<"num_channels     : "<<format_chunk.num_channels<<endl;
	cout<<"sample_rate      : "<<format_chunk.sample_rate<<endl;
	cout<<"byte_rate        : "<<format_chunk.byte_rate<<endl;
	cout<<"block_align      : "<<format_chunk.block_align<<endl;
	cout<<"bits_per_sample  : "<<format_chunk.bits_per_sample<<endl;
	cout<<"########## Data Chunk ##########"<<endl;
	cout<<"chunk_id         : "<<charToString(data_chunk.chunk_id)<<endl;
	cout<<"chunk_size       : "<<data_chunk.chunk_size<<endl;
	cout<<"datas            : [...]"<<endl;
}/*}}}*/

Wave::Wave (string filename)
{/*{{{*/
	read (filename);
}/*}}}*/

bool Wave::read (string filename)
{/*{{{*/
	ifs = ifstream(filename, ios::binary);
	if (!ifs) {
		cerr<<"Cannot open "<<filename<<endl;
		return false;
	}

	return readChunk ();
}/*}}}*/

bool Wave::write (string filename)
{/*{{{*/
	ofs = ofstream(filename, ios::binary);
	if (!ofs) {
		cerr<<"Cannot open "<<filename<<endl;
		return false;
	}

	return writeChunk();
}/*}}}*/

bool Wave::readChunk ()
{/*{{{*/
	// ########## read riff chunk ##########
	readBin(riff_chunk.chunk_id);
	if (charToString(riff_chunk.chunk_id) != "RIFF") {
		cerr<<"Cannot read RiffChunk header."<<endl;
		return false;
	}

	readBin(riff_chunk.chunk_size);
	readBin(riff_chunk.format);
	if (charToString(riff_chunk.format) != "WAVE") {
		cerr<<"This file is not wave format."<<endl;
		return false;
	}


	// ########## read format chunk ##########
	readBin(format_chunk.chunk_id);
	if (charToString(format_chunk.chunk_id) != "fmt ") {
		cerr<<"Cannot read FormatChunk header."<<endl;
		return false;
	}

	readBin(format_chunk.chunk_size);
	if (format_chunk.chunk_size != 16) {
		cerr<<"This file is not linear PCM format."<<endl;
		return false;
	}

	readBin(format_chunk.audio_format);
	readBin(format_chunk.num_channels);
	readBin(format_chunk.sample_rate);
	readBin(format_chunk.byte_rate);
	readBin(format_chunk.block_align);
	readBin(format_chunk.bits_per_sample);


	// ########## read data chunk ##########
	readBin(data_chunk.chunk_id);
	if (charToString(data_chunk.chunk_id) != "data") {
		cerr<<"Cannot read DataChunk header."<<endl;
		return false;
	}

	readBin(data_chunk.chunk_size);

	for (int i=0; i<data_chunk.chunk_size; i+=format_chunk.bits_per_sample/8) {
		int32_t data = 0;
		ifs.read((char*)&data, format_chunk.bits_per_sample/8);
		data_chunk.datas.push_back(dataToInt32(data));
	}

	return true;
}/*}}}*/

template<typename T> void Wave::readBin (T& data)
{/*{{{*/
	ifs.read((char*)&data, sizeof(data));
}/*}}}*/

bool Wave::writeChunk ()
{/*{{{*/
	// ##### write riff chunk #####
	writeBin(riff_chunk.chunk_id);
	writeBin(riff_chunk.chunk_size);
	writeBin(riff_chunk.format);

	// ##### write format chunk #####
	writeBin(format_chunk.chunk_id);
	writeBin(format_chunk.chunk_size);
	writeBin(format_chunk.audio_format);
	writeBin(format_chunk.num_channels);
	writeBin(format_chunk.sample_rate);
	writeBin(format_chunk.byte_rate);
	writeBin(format_chunk.block_align);
	writeBin(format_chunk.bits_per_sample);

	// ##### write data chunk #####
	writeBin(data_chunk.chunk_id);
	writeBin(data_chunk.chunk_size);

	for (auto data : data_chunk.datas) {
		ofs.write((char*)&data, format_chunk.bits_per_sample/8);
	}

	return true;
}/*}}}*/

template<typename T> void Wave::writeBin (T& data)
{/*{{{*/
	ofs.write((char*)&data, sizeof(data));
}/*}}}*/

int32_t Wave::dataToInt32 (int32_t data)
{/*{{{*/
	if (data & (1 << (format_chunk.bits_per_sample-1))) {
		uint32_t mask = 0xffff << format_chunk.bits_per_sample;
		data = data | mask;
	}
	return data;
}/*}}}*/

template<typename T> string Wave::charToString (T& data)
{/*{{{*/
	string output;
	for (int i=0; i<sizeof(data); ++i) {
		output.push_back(data[i]);
	}
	return output;
}/*}}}*/
