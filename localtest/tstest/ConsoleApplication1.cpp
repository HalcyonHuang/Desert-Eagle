// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <stdint.h>
#include <stdio.h>

static unsigned int crc_tab[256] = {
    0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b,
    0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
    0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7,
    0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
    0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,
    0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
    0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef,
    0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
    0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb,
    0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
    0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0,
    0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
    0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4,
    0x0808d07d, 0x0cc9cdca, 0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
    0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,
    0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
    0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc,
    0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
    0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050,
    0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
    0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34,
    0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
    0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1,
    0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
    0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,
    0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
    0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 0xf12f560e, 0xf5ee4bb9,
    0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
    0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd,
    0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
    0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71,
    0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
    0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2,
    0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
    0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,
    0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
    0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a,
    0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
    0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676,
    0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
    0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662,
    0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
    0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

static unsigned int  calc_crc32 (unsigned char *data, unsigned int datalen)
{
    unsigned int i;
    unsigned int crc = 0xffffffff;

    for (i=0; i<datalen; i++) 
    {
        crc = (crc << 8) ^ crc_tab[((crc >> 24) ^ *data++) & 0xff];
    }
    return crc;
}

uint32_t programpid = -1;
uint32_t  videoid = -1;

#define TS_FIXED_LENGTH 188

typedef struct ts_header
{  
    unsigned sync_byte                                  :8;
    unsigned transport_error_indicator           :1;
    unsigned unspayload_unit_start_indicator :1;
    unsigned transport_priority                       :1;
    unsigned pid                                            :13;
    unsigned transport_scrambling_control    :2;
    unsigned adaptation_field_control            :2;
    unsigned continuity_counter                    :4;

    // just for pcr flags
    uint64_t  u64pcrbase;// start from 897600 pts 900000  then increment
    
    void print()
    {
        printf("ts header: sync_byte : 0x%x unit_start: 0x%x  pid : 0x%x  scrambing: 0x%x, adatation_fild: 0x%x, counter:0x%x pcrbase :%llu\r\n", 
                  this->sync_byte, this->unspayload_unit_start_indicator, this->pid, this->transport_scrambling_control,
                  this->adaptation_field_control, this->continuity_counter, this->u64pcrbase);
    }
}ts_header; 

int get_ts_header(ts_header* pheader, uint8_t* szbuffer)
{
    pheader->sync_byte = szbuffer[0];
    pheader->transport_error_indicator = szbuffer[1]>>7;
    pheader->unspayload_unit_start_indicator = (szbuffer[1]>>6) & 0x1;
    pheader->transport_priority  = (szbuffer[1]>>5) & 0x1;
    pheader->pid = ((szbuffer[1]&0x1f) <<8) | szbuffer[2];
    pheader->transport_scrambling_control = szbuffer[3] >> 6 &0x3;
    pheader->adaptation_field_control = szbuffer[3] >> 4 &0x3;
    pheader->continuity_counter = szbuffer[3] & 0xf;

    pheader->u64pcrbase = 0;
    int npos = 4;
    // still have some question
    if (pheader->unspayload_unit_start_indicator || pheader->adaptation_field_control & 0x2)
    {
        uint8_t nadaptionlen = szbuffer[4];
        npos += 1;
        if (nadaptionlen >= 0)        
        {
            npos +=  nadaptionlen;            
            uint8_t flags = szbuffer[5];
            if (flags & 0x10)
            {
                // pcr flags
                pheader->u64pcrbase = szbuffer[6] << 25 | szbuffer[7] << 17 | szbuffer[8] << 9| szbuffer[9]<<1 | szbuffer[10]>>7;
            }
        }        
    }
    return npos;
}

#include <vector>
typedef struct ts_pat_program  
{  
    unsigned program_number    :16;   //节目号  
    unsigned reversed                  :3;
    unsigned program_map_PID   :13;   //节目映射表的PID，节目号大于0时对应的PID，每个节目对应一个  
}ts_pat_program; 

typedef struct ts_pat  
{  
    unsigned table_id                     : 8; //固定为0x00 ，标志是该表是PAT  
    unsigned section_syntax_indicator     : 1; //段语法标志位，固定为1  
    unsigned zero                         : 1; //0  
    unsigned reserved_1                   : 2; // 保留位  
    unsigned section_length               : 12; //表示这个字节后面有用的字节数，包括CRC32  
    unsigned transport_stream_id        : 16; //该传输流的ID，区别于一个网络中其它多路复用的流  
    unsigned reserved_2                   : 2;// 保留位  
    unsigned version_number               : 5; //范围0-31，表示PAT的版本号  
    unsigned current_next_indicator       : 1; //发送的PAT是当前有效还是下一个PAT有效  
    unsigned section_number               : 8; //分段的号码。PAT可能分为多段传输，第一段为00，以后每个分段加1，最多可能有256个分段  
    unsigned last_section_number          : 8;  //最后一个分段的号码  

    std::vector<ts_pat_program> program;
    unsigned reserved_3                    : 3; // 保留位  
    unsigned network_PID                    : 13; //网络信息表（NIT）的PID,节目号为0时对应的PID为network_PID  
    unsigned CRC_32                        : 32;  //CRC32校验码  
    void print()
    {
        printf("\t tableid:0x%x, section_length:0x%x, stream_id:0x%x, version_num:0x%x, current_nex_ind:0x%x, \r\n"
                "\t\t section_num:0x%x, last_sec_num:0x%x, crc:0x%x \r\n", 
            this->table_id, this->section_length, this->transport_stream_id, this->version_number,
            this->current_next_indicator, this->section_number, this->last_section_number, this->CRC_32);        
        for (auto &i : program)
        {
            printf("\t\t programnumber:0x%x, pid:0x%x\r\n", i.program_number, i.program_map_PID);
        }
    }
    
} ts_pat;

unsigned int TS_network_Pid = -1;
int get_pat_table( ts_pat * packet, unsigned char * buffer)
{
    packet->table_id                    = buffer[0];  
    packet->section_syntax_indicator    = buffer[1] >> 7;  
    packet->zero                        = buffer[1] >> 6 & 0x1;  
    packet->reserved_1                  = buffer[1] >> 4 & 0x3;  
    packet->section_length              = (buffer[1] & 0x0F) << 8 | buffer[2];
    packet->transport_stream_id           = buffer[3] << 8 | buffer[4];  
    packet->reserved_2                    = buffer[5] >> 6;  
    packet->version_number                = buffer[5] >> 1 &  0x1F;  
    packet->current_next_indicator        = (buffer[5] << 7) >> 7;
    packet->section_number                = buffer[6];
    packet->last_section_number           = buffer[7];   

    int len = 0;  
    len = 3 + packet->section_length;  
    packet->CRC_32                        = (buffer[len-4] & 0x000000FF) << 24  
        | (buffer[len-3] & 0x000000FF) << 16  
        | (buffer[len-2] & 0x000000FF) << 8   
        | (buffer[len-1] & 0x000000FF);   

    int n = 0;  
    for ( n = 0; n < packet->section_length - 9; n += 4 )  
    {  
        unsigned  program_num = buffer[8 + n ] << 8 | buffer[9 + n ];    
        packet->reserved_3           = buffer[10 + n ] >> 5;   

        packet->network_PID = 0x00;
        if ( program_num == 0x00)  
        {
            packet->network_PID = (buffer[10 + n ] & 0x1F) << 8 | buffer[11 + n ];
        }  
        else  
        {  
            ts_pat_program PAT_program;  
            PAT_program.program_map_PID = (buffer[10 + n] & 0x1F) << 8 | buffer[11 + n];
            PAT_program.program_number = program_num;  
            packet->program.push_back( PAT_program );
        }           
    }  
    return 0;  
}  

void add_counter(uint8_t& counter)
{
    // max is 0x f
    counter++;
    counter = counter % 0x10;
}
int write_ts_header(uint8_t* szbuffer, uint16_t pid, uint8_t payload_unit_start, uint8_t transport_priority, uint8_t adapter_field, uint8_t& counter)
{
    ts_header header;
    header.sync_byte = 0x47;
    header.transport_error_indicator = 0;
    header.unspayload_unit_start_indicator = payload_unit_start;
    header.transport_priority = transport_priority;
    header.pid = pid;
    header.transport_scrambling_control = 0x0;
    header.adaptation_field_control = adapter_field;
    header.continuity_counter = counter;
    szbuffer[0] = header.sync_byte;
    szbuffer[1] = header.transport_error_indicator << 7 | header.unspayload_unit_start_indicator << 6  | header.transport_priority << 5 | 
                         ((header.pid >> 8) & 0x1f);
    szbuffer[2] = (header.pid & 0xff);
    szbuffer[3] = header.transport_scrambling_control << 6 | header.adaptation_field_control << 4 | header.continuity_counter;
    add_counter(counter);
    return 4;
}

uint8_t g_npatcounte = 0;

int write_pat(uint8_t* szbuffer, uint8_t& counter)
{    
    memset(szbuffer, 0xFF, TS_FIXED_LENGTH);
    int npos = 0;
    npos += write_ts_header(szbuffer, 0, 1, 0, 1, counter);
    szbuffer[4] = 0;

    npos = 5;

    ts_pat tspat;
    tspat.table_id = 0x00;
    tspat.section_syntax_indicator = 0x01;
    tspat.zero = 0x00;
    tspat.reserved_1 = 0x03;                                               //设置为11；
    tspat.section_length = 0x0d;                                           //pat结构体长度 16个字节减去上面的3个字节
    tspat.transport_stream_id = 0x01;
    tspat.reserved_2 = 0x03;                                               //设置为11；
    tspat.version_number = 0x00;
    tspat.current_next_indicator = 0x01;                                   //当前的pat 有效
    tspat.section_number = 0x00;
    tspat.last_section_number = 0x00;    
    tspat.reserved_3 = 0x07;                                               //设置为111；    
    
    uint16_t program_number = 1;
    uint16_t program_map_PID = 0x100;
    szbuffer[npos] = tspat.table_id;
    szbuffer[npos + 1] = tspat.section_syntax_indicator << 7 | tspat.zero  << 6 | tspat.reserved_1 << 4 | ((tspat.section_length >> 8) & 0x0F);
    szbuffer[npos + 2] = tspat.section_length & 0x00FF;
    szbuffer[npos + 3] = tspat.transport_stream_id >> 8;
    szbuffer[npos + 4] = tspat.transport_stream_id & 0x00FF;
    szbuffer[npos + 5] = tspat.reserved_2 << 6 | tspat.version_number << 1 | tspat.current_next_indicator;
    szbuffer[npos + 6] = tspat.section_number;
    szbuffer[npos + 7] = tspat.last_section_number;
    szbuffer[npos + 8] = program_number>>8;
    szbuffer[npos + 9] = program_number & 0xff;
    szbuffer[npos + 10]= tspat.reserved_3 << 5 | ((program_map_PID >> 8) & 0x0F);
    szbuffer[npos + 11]= program_map_PID & 0x00FF;

    // getcrc
    npos += 12;
    uint32_t dwcrc = calc_crc32(&szbuffer[5], 12);
    szbuffer[npos] = (dwcrc >> 24) & 0xff;
    szbuffer[npos + 1] = (dwcrc >> 16) & 0xff;
    szbuffer[npos + 2] = (dwcrc >> 8) & 0xff;
    szbuffer[npos + 3] = dwcrc & 0xff;
    
    return TS_FIXED_LENGTH;
}

typedef struct ts_pmt_stream  
{  
    unsigned stream_type     : 8; //指示特定PID的节目元素包的类型。该处PID由elementary PID指定  
    unsigned elementary_pid  : 13; //该域指示TS包的PID值。这些TS包含有相关的节目元素  
    unsigned es_info_length  : 12; //前两位bit为00。该域指示跟随其后的描述相关节目元素的byte数  
    unsigned descriptor;  
}ts_pmt_stream;  

typedef struct ts_pmt  
{  
    unsigned table_id                   : 8; //固定为0x02, 表示PMT表  
    unsigned section_syntax_indicator    : 1; //固定为0x01  
    unsigned zero                       : 1; //0x01  
    unsigned reserved_1                 : 2; //0x03  
    unsigned section_length : 12;//首先两位bit置为00，它指示段的byte数，由段长度域开始，包含CRC  
    unsigned program_number             : 16;// 指出该节目对应于可应用的Program map PID  
    unsigned reserved_2                 : 2; //0x03  
    unsigned version_number             : 5; //指出TS流中Program map section的版本号  
    unsigned current_next_indicator  : 1; //当该位置1时，当前传送的Program map section可用  
    //当该位置0时，指示当前传送的Program map section不可用，下一个TS流的Program map section有效  
    unsigned section_number            : 8; //固定为0x00  
    unsigned last_section_number      : 8; //固定为0x00  
    unsigned reserved_3               : 3; //0x07  
    unsigned pcr_pid                   : 13; //指明TS包的PID值，该TS包含有PCR域，  
    //该PCR值对应于由节目号指定的对应节目，如果对于私有数据流的节目定义与PCR无关，这个域的值将为0x1FFF。  
    unsigned reserved_4            : 4;  //预留为0x0F  
    unsigned program_info_length  : 12; //前两位bit为00。该域指出跟随其后对节目信息的描述的byte数。  

    std::vector<ts_pmt_stream> PMT_Stream;  //每个元素包含8位, 指示特定PID的节目元素包的类型。该处PID由elementary PID指定  
    unsigned reserved_5                : 3; //0x07  
    unsigned reserved_6                : 4; //0x0F  
    unsigned crc_32                    : 32;   

    // fro simply
    unsigned char stream_type_video : 8;         //指示特定PID的节目元素包的类型。该处PID由elementary PID指定
    unsigned char reserved_5_video: 3;           //0x07
    unsigned int elementary_PID_video: 13;       //该域指示TS包的PID值。这些TS包含有相关的节目元素
    unsigned char reserved_6_video : 4;          //0x0F
    unsigned int ES_info_length_video : 12;      //前两位bit为00。该域指示跟随其后的描述相关节目元素的byte数
    unsigned char stream_type_audio : 8;         //指示特定PID的节目元素包的类型。该处PID由elementary PID指定
    unsigned char reserved_5_audio: 3;           //0x07
    unsigned int elementary_PID_audio: 13;       //该域指示TS包的PID值。这些TS包含有相关的节目元素
    unsigned char reserved_6_audio : 4;          //0x0F
    unsigned int ES_info_length_audio : 12;      //前两位bit为00。该域指示跟随其后的描述相关节目元素的byte数
    void print()
    {
        printf("\t table_id:0x%x， sectionlen:0x%x, programnum:0x%x, vernum:0x%x, curnext_ind:0x%x, \r\n"
                  "\t\tsec_num:0x%x, last_secnum:0x%x, pcr_pid:0x%x, program_info_len:0x%x, crc:0x%x\r\n",
                    table_id, section_length, program_number, version_number, current_next_indicator, 
                    section_number, last_section_number, pcr_pid, program_info_length, crc_32);
        for (auto &i : PMT_Stream)
        {
            printf("\t\t streamtype :0x%x, elempid:0x%x, infolength:0x%x, descripotr:0x%x \r\n",
                     i.stream_type, i.elementary_pid, i.es_info_length, i.descriptor);
        }
    }
} ts_pmt; 

int get_pmt_table ( ts_pmt * packet, unsigned char * buffer )  
{   
    packet->table_id                         = buffer[0];  
    packet->section_syntax_indicator         = buffer[1] >> 7;  
    packet->zero                             = buffer[1] >> 6 & 0x01;   
    packet->reserved_1                       = buffer[1] >> 4 & 0x03;  
    packet->section_length                   = (buffer[1] & 0x0F) << 8 | buffer[2];
    packet->program_number                   = buffer[3] << 8 | buffer[4];  
    packet->reserved_2                       = buffer[5] >> 6;  
    packet->version_number                   = buffer[5] >> 1 & 0x1F;  
    packet->current_next_indicator           = (buffer[5] << 7) >> 7;  
    packet->section_number                   = buffer[6];  
    packet->last_section_number              = buffer[7];  
    packet->reserved_3                       = buffer[8] >> 5;  
    packet->pcr_pid                          = ((buffer[8] << 8) | buffer[9]) & 0x1FFF;
    packet->reserved_4                       = buffer[10] >> 4;  
    packet->program_info_length              = (buffer[10] & 0x0F) << 8 | buffer[11];   
    // Get CRC_32  
    int len = 0;  
    len = packet->section_length + 3;      
    packet->crc_32                = (buffer[len-4] & 0x000000FF) << 24  
        | (buffer[len-3] & 0x000000FF) << 16  
        | (buffer[len-2] & 0x000000FF) << 8  
        | (buffer[len-1] & 0x000000FF);   

    int pos = 12;
    // program info descriptor  
    if ( packet->program_info_length != 0 )  
        pos += packet->program_info_length;
    // Get stream type and PID
    for ( ; pos < (len-4); )
    {  
        ts_pmt_stream pmt_stream;
        pmt_stream.stream_type =  buffer[pos];
        packet->reserved_5  =  buffer[pos+1] >> 5;  
        pmt_stream.elementary_pid = ((buffer[pos+1] << 8) | buffer[pos+2]) & 0x1FFF;  
        packet->reserved_6    =  buffer[pos+3] >> 4;  
        pmt_stream.es_info_length =  (buffer[pos+3] & 0x0F) << 8 | buffer[pos+4];  

        pmt_stream.descriptor = 0x00;  
        if (pmt_stream.es_info_length != 0)  
        {  
            pmt_stream.descriptor = buffer[pos + 5];  

            for( int len = 2; len <= pmt_stream.es_info_length; len ++ )  
            {  
                pmt_stream.descriptor = pmt_stream.descriptor<< 8 | buffer[pos + 4 + len];  
            }  
            pos += pmt_stream.es_info_length;  
        }  
        pos += 5;  
        packet->PMT_Stream.push_back( pmt_stream );
    }  
    return 0;  
}  

int write_pmt(uint8_t* szbuffer, uint8_t& counter)
{
    memset(szbuffer, 0xFF, TS_FIXED_LENGTH);
    int npos = 0;
    npos += write_ts_header(szbuffer, 0x100, 1, 0, 1, counter);
    szbuffer[4] = 0;

    npos = 5;
    uint16_t h264pid = 0x102;
    uint16_t aacpid = 0x101;

    ts_pmt tspmt;
    tspmt.table_id = 0x02;
    tspmt.section_syntax_indicator = 0x01;
    tspmt.zero = 0x00;
    tspmt.reserved_1 = 0x03;
    tspmt.section_length = 12 + 5 + 5 + 4 - 3;                                           //PMT结构体长度 12 + 5 + 5 + 4 个字节减去前面的3个字节
    tspmt.program_number = 01;                                             //只有一个节目
    tspmt.reserved_2 = 0x03;
    tspmt.version_number = 0x00;
    tspmt.current_next_indicator = 0x01;                                   //当前的PMT有效
    tspmt.section_number = 0x00;
    tspmt.last_section_number = 0x00;
    tspmt.reserved_3 = 0x07;
    tspmt.pcr_pid = h264pid ;                                          //视频PID                                   
    tspmt.reserved_4 = 0x0F;
    tspmt.program_info_length = 0x00;                                      //后面无 节目信息描述

    tspmt.stream_type_video = 0x1b;                       //视频的类型
    tspmt.reserved_5_video = 0x07;
    tspmt.elementary_PID_video = h264pid;                              //视频的PID
    tspmt.reserved_6_video= 0x0F;
    tspmt.ES_info_length_video = 0x00;                                     //视频无跟随的相关信息

    tspmt.stream_type_audio = 0xf;                       //音频类型
    tspmt.reserved_5_audio = 0x07;
    tspmt.elementary_PID_audio = aacpid;                               //音频PID 
    tspmt.reserved_6_audio = 0x0F;
    tspmt.ES_info_length_audio = 0x00;                                     //音频无跟随的相关信息

    szbuffer[npos + 0] = tspmt.table_id;
    szbuffer[npos + 1] = tspmt.section_syntax_indicator << 7 | tspmt.zero  << 6 | tspmt.reserved_1 << 4 | ((tspmt.section_length >> 8) & 0x0F);
    szbuffer[npos + 2] = tspmt.section_length & 0xff;
    szbuffer[npos + 3] = tspmt.program_number >> 8;
    szbuffer[npos + 4] = tspmt.program_number & 0xff;
    szbuffer[npos + 5] = tspmt.reserved_2 << 6 | tspmt.version_number << 1 | tspmt.current_next_indicator;
    szbuffer[npos + 6] = tspmt.section_number;
    szbuffer[npos + 7] = tspmt.last_section_number;
    szbuffer[npos + 8] = tspmt.reserved_3 << 5  | ((tspmt.pcr_pid >> 8) & 0x1F);
    szbuffer[npos + 9] = tspmt.pcr_pid & 0x0FF;
    szbuffer[npos + 10]= tspmt.reserved_4 << 4 | ((tspmt.program_info_length >> 8) & 0x0F);
    szbuffer[npos + 11]= tspmt.program_info_length & 0xFF;
    
    szbuffer[npos + 12]= tspmt.stream_type_audio;                               //音频流的stream_type
    szbuffer[npos + 13]= tspmt.reserved_5_audio<< 5 | ((tspmt.elementary_PID_audio >> 8 ) & 0x1F);
    szbuffer[npos + 14]= tspmt.elementary_PID_audio & 0x00FF;
    szbuffer[npos + 15]= tspmt.reserved_6_audio << 4 | ((tspmt.ES_info_length_audio >> 8) & 0x0F);
    szbuffer[npos + 16]= tspmt.ES_info_length_audio & 0x0FF;

    szbuffer[npos + 17]= tspmt.stream_type_video;                               //视频流的stream_type
    szbuffer[npos + 18]= tspmt.reserved_5_video << 5 | ((tspmt.elementary_PID_video >> 8 ) & 0x1F);
    szbuffer[npos + 19]= tspmt.elementary_PID_video & 0x00FF;
    szbuffer[npos + 20]= tspmt.reserved_6_video<< 4 | ((tspmt.ES_info_length_video >> 8) & 0x0F);
    szbuffer[npos + 21]= tspmt.ES_info_length_video & 0x0FF;
    npos += 22;

    // reset section length
    int sectionlen  = npos - 8 + 4;  // - 5 - 3 + 4    
    szbuffer[6] = 0xb0 | (sectionlen >> 8);
    szbuffer[7] = sectionlen&0xff;

    uint32_t dwcrc = calc_crc32(&szbuffer[5], npos-5);
    szbuffer[npos] = (dwcrc >> 24) & 0xff;
    szbuffer[npos + 1] = (dwcrc >> 16) & 0xff;
    szbuffer[npos + 2] = (dwcrc >> 8) & 0xff;
    szbuffer[npos + 3] = dwcrc & 0xff;    
    return TS_FIXED_LENGTH;
}

typedef struct pes_header
{  
    uint8_t packet_start_code_prefix[3];
    uint8_t stream_id;
    uint16_t pes_packet_length;
    unsigned  marker_bits : 2; //0x2 b10
    unsigned pes_scrambling_control : 2;
    unsigned pes_priority:1;
    unsigned data_alignment_indicator:1;
    unsigned copyright:1;
    unsigned original_or_copy:1;
    unsigned pts_dts_flags:2;
    unsigned escr_flag:1;
    unsigned es_rate_flag:1;
    unsigned dsm_trick_mode_flag:1;
    unsigned Additional_copy_info_flag:1;
    unsigned pes_crc_flag:1;
    unsigned pes_extension_flag:1;
    unsigned pes_header_data_length:8;
    uint64_t dwpts;
    uint64_t dwdts;
    void print()
    {
        printf("\t\t ts start_code:%x%x%x, streamid:0x%x, packetlen:0x%x, pts_dts_flag:0x%x, \r\n"
            "\t\t  header_len:0x%x, pts %llu  dts %llu\r\n", 
            packet_start_code_prefix[0], packet_start_code_prefix[1], packet_start_code_prefix[2],
            stream_id, pes_packet_length, pts_dts_flags, pes_header_data_length, dwpts, dwdts);
    }
}pes_header; 

int get_pes_header(pes_header* pes, uint8_t* szbuffer)
{
    memcpy(pes->packet_start_code_prefix, szbuffer, 3);
    pes->stream_id = szbuffer[3];
    pes->pes_packet_length = szbuffer[4] << 8 | szbuffer[5];
    pes->pts_dts_flags = szbuffer[7]>>6;
    pes->pes_header_data_length = szbuffer[8];

    pes->dwpts = 0;
    pes->dwdts = 0;
    if (pes->pts_dts_flags & 0x2)
    {
        // 5 bytes
        pes->dwpts = ((szbuffer[9]>>1)&0x7)<<30   | (szbuffer[10]<<22) | (szbuffer[11]>>1)<<15 | (szbuffer[12]<<7) | (szbuffer[13]>>1); 
    }
    if (pes->pts_dts_flags & 0x1)
    {
        pes->dwdts = ((szbuffer[14]>>1)&0x7)<<30   | (szbuffer[15]<<22) | (szbuffer[16]>>1)<<15 | (szbuffer[17]<<7) | (szbuffer[18]>>1); 
    }
    return pes->pes_header_data_length + 9;
}


int write_pes_h264(uint8_t* ph264, uint32_t dwh264len, uint64_t u64time, uint8_t* szbuffer, uint8_t& counter)
{    
    // audio no pcr    
    int pcrlen = 7;
    int esheader = 19;
    int ntotalpacket = (1 + pcrlen + dwh264len +esheader + 183) / 184;
    int nconsumeh264 = 0;
    
    for(int inx = 0; inx < ntotalpacket; inx++)
    {
        int nlefth264 = dwh264len - nconsumeh264;
        int nleftspace = TS_FIXED_LENGTH - 4;        
        int adapterlen = 0;
        if (0 == inx)
        {
            nleftspace = TS_FIXED_LENGTH - 4 - 1 - pcrlen - esheader;
        }
        if (nleftspace > nlefth264)
        {
            adapterlen = nleftspace - nlefth264;
            memset(&szbuffer[inx*TS_FIXED_LENGTH], 0xff, TS_FIXED_LENGTH);
        }

        int npos = inx*TS_FIXED_LENGTH;
        if (0 == inx)
        {
            pes_header pes;
            pes.stream_id = 0xe0;
            pes.marker_bits = 0x2;
            pes.pes_scrambling_control = 0;
            pes.pes_priority = 0;
            pes.data_alignment_indicator = 1;
            pes.copyright = 0;
            pes.original_or_copy = 0;

            pes.pts_dts_flags = 0x3;// 2bits
            pes.escr_flag= 0;
            pes.es_rate_flag = 0;
            pes.dsm_trick_mode_flag = 0;
            pes.Additional_copy_info_flag = 0;
            pes.pes_crc_flag = 0;
            pes.pes_extension_flag =  0;

            pes.pes_header_data_length = 0xa; // pts dts

            write_ts_header(&szbuffer[npos], 0x102, 1, 0, 3, counter);
            szbuffer[npos+4] = 7 + adapterlen;
            szbuffer[npos+5] = 0x10; // just pcr info
            szbuffer[npos+6] = u64time >> 25 & 0xff;
            szbuffer[npos+7] = u64time >> 17 & 0xff;
            szbuffer[npos+8] = u64time >> 9 & 0xff;
            szbuffer[npos+9] = u64time >> 1 & 0xff;
            szbuffer[npos+10] = (u64time & 0x1)<<7 | 0x3f<<1 ;// reversed 6 bits  ext is 0, 
            szbuffer[npos+11] = 0;
            npos += 12;
            npos += adapterlen;

            szbuffer[npos + 0] = 0x0;
            szbuffer[npos + 1] = 0x0;
            szbuffer[npos + 2] = 0x1;
            szbuffer[npos + 3] = pes.stream_id;
            szbuffer[npos + 4] = 0; //packet length is 0
            szbuffer[npos + 5] = 0; // packet length is 0
            szbuffer[npos + 6] = pes.marker_bits << 6 | pes.pes_scrambling_control << 4 | pes.pes_priority << 3 |
                pes.data_alignment_indicator << 2 | pes.copyright << 1 |pes.original_or_copy;
            szbuffer[npos + 7] = pes.pts_dts_flags << 6 | pes.escr_flag<< 5 | pes.es_rate_flag << 4 |
                pes.dsm_trick_mode_flag << 3 | pes.Additional_copy_info_flag << 2 | pes.pes_crc_flag << 1 | pes.pes_extension_flag;
            szbuffer[npos + 8] = pes.pes_header_data_length;
            npos += 9;
            // pes header szbuffer[npos+4+8]
            szbuffer[npos + 0] = (0x3 << 4) | ((u64time >> 30)&0x07)<<1 | 0x1; 
            szbuffer[npos + 1]= (u64time >> 22) & 0xff;
            szbuffer[npos + 2]= ((u64time >> 15)&0x7f)<<1 | 0x1;
            szbuffer[npos + 3]= (u64time >> 7) & 0xff;
            szbuffer[npos + 4]= (u64time & 0x7f)<<1 | 0x1;

            szbuffer[npos + 5] = (0x1 << 4) | ((u64time >> 30)&0x07)<<1 | 0x1; 
            szbuffer[npos + 6]= szbuffer[npos + 1];
            szbuffer[npos + 7]= szbuffer[npos + 2];
            szbuffer[npos + 8]= szbuffer[npos + 3];
            szbuffer[npos + 9]= szbuffer[npos + 4];
            npos += 10;
            // then h264 data
            int ncopy = inx*TS_FIXED_LENGTH+TS_FIXED_LENGTH-npos;
            memcpy(&szbuffer[npos], &ph264[nconsumeh264], ncopy);
            nconsumeh264 += ncopy;
        }
        else
        {
            uint8_t byadaptaionfiled = 1;
            if (adapterlen> 0) {byadaptaionfiled = 0x3;}
            write_ts_header(&szbuffer[npos], 0x102, 0, 0, byadaptaionfiled, counter);
            
            if (adapterlen > 0)
            {
                szbuffer[npos+4] = adapterlen -1;
                szbuffer[npos+5] = 00;
            }
            npos += 4;
            npos += adapterlen;  

            int ncopy = inx*TS_FIXED_LENGTH+TS_FIXED_LENGTH-npos;
            memcpy(&szbuffer[npos], &ph264[nconsumeh264], ncopy);
            nconsumeh264 += ncopy;
        }
               
    }

    return ntotalpacket*TS_FIXED_LENGTH;
}

uint8_t g_szh264frame[512*1024];
uint8_t g_szts[512*1024];
uint32_t g_dwframelen = 0;


int _tmain(int argc, _TCHAR* argv[])
{
    if (1)
    {
        FILE* pfile = fopen("D:\\test.h264", "rb");
        if (!pfile)
        {
            printf("read file error\r\n");
            return -1;
        }

        FILE* ptsfile = fopen("d:\\myts.ts", "wb");
        int writepat = 0;
        uint8_t patcountter = 0;
        uint8_t pmtcountter = 0;
        uint8_t h264counter = 0;
        uint64_t dwtimebase = 900000;
        while (1)
        {
            int len = 0;
            int nread = fread(&len, 1, 4, pfile);
            if (nread != 4) break;

            nread = fread(g_szh264frame, 1, len, pfile);
            if (nread != len) break;

            printf("read %d\r\n", len);

            if (writepat % 10 == 0)
            {
                writepat ++;                
                uint8_t szbuffer[1*1024];                
                int xxx = write_pat(szbuffer, patcountter);            
                fwrite(szbuffer, xxx, 1, ptsfile);
                xxx = write_pmt(szbuffer, pmtcountter);            
                fwrite(szbuffer, xxx, 1, ptsfile);
            }            
            int xxxx = write_pes_h264(g_szh264frame, len, dwtimebase, g_szts, h264counter);
            fwrite(g_szts, xxxx, 1, ptsfile);
            dwtimebase += 3600;
            
            // write to ts file
            
        }
        fclose(pfile);
        fclose(ptsfile);
    }
    else
    {
        FILE* pfile = fopen("D:\\github\\bipbop-gear1-all_2.ts", "rb");
        uint8_t szbuffer[TS_FIXED_LENGTH];
        int x = 0;
        while (!feof(pfile))
        {
            fread(szbuffer, TS_FIXED_LENGTH, 1, pfile);
            ts_header header;        
            int npos = get_ts_header(&header, szbuffer);
            header.print();

            // real buffer 
            if (header.pid == 0)
            {
                ts_pat tpat;
                get_pat_table(&tpat, &szbuffer[npos]);
                tpat.print();
                programpid = tpat.program[0].program_map_PID;
            }
            if (header.pid == programpid)
            {
                //pmt
                ts_pmt tpmt;
                get_pmt_table(&tpmt, &szbuffer[npos]);            
                tpmt.print();
                for (auto & it : tpmt.PMT_Stream)
                {
                    if (it.stream_type == 0x1b)
                    {
                        videoid = it.elementary_pid;
                        break;
                    }
                }
            }
            if (header.pid == videoid)
            {
                // parse video
                if (header.unspayload_unit_start_indicator)
                {
                    if (g_dwframelen > 0)
                    {                        
                        FILE* ph264 = fopen("d:\\h264fromts2.h264", "ab+");
                        fwrite(&g_dwframelen, 4, 1, ph264);
                        fwrite(g_szh264frame, g_dwframelen, 1, ph264);
                        fclose(ph264);
                        g_dwframelen = 0;
                    }
                    // parse pes
                    pes_header pesheader;
                    int npesheader = get_pes_header(&pesheader, &szbuffer[npos]);
                    pesheader.print();
                    int bufferindex = npos + npesheader;
                    int nleft = TS_FIXED_LENGTH - bufferindex;
                    if (nleft > 0)
                    {
                        memcpy(&g_szh264frame[g_dwframelen], &szbuffer[bufferindex], nleft);
                        g_dwframelen += nleft;
                    }
                }
                else
                {                    
                    int nleft = TS_FIXED_LENGTH - npos;                    
                    memcpy(&g_szh264frame[g_dwframelen], &szbuffer[npos], nleft);
                    g_dwframelen += nleft;
                }

            }
            x++;
            if (x > 100)
            {
                break;
            } 
        }
        fclose(pfile);
    }
    
    
    return 0;
}

