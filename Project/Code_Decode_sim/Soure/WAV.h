#ifndef _WAV_H_BAB
#define _WAV_H_BAB

typedef  unsigned	char	u8;
typedef				char	s8;
typedef  unsigned	short	u16;
typedef				short	s16;
typedef  unsigned	int		u32;
typedef				int		s32;

/*
printf("sizeof(u8)=%d\n",sizeof(u8));
printf("sizeof(s8)=%d\n",sizeof(s8));
printf("sizeof(u16)=%d\n",sizeof(u16));
printf("sizeof(s16)=%d\n",sizeof(s16));
printf("sizeof(u32)=%d\n",sizeof(u32));
printf("sizeof(s32)=%d\n",sizeof(s32));
*/

struct RIFF_HEADER_DEF
{
	s8 riff_id[4];     // 'R','I','F','F'
	u32 riff_size;
	s8 riff_format[4]; // 'W','A','V','E'
};

struct WAVE_FORMAT_DEF
{
	u16 FormatTag;
	u16 Channels;
	u32 SamplesPerSec;
	u32 AvgBytesPerSec;
	u16 BlockAlign;
	u16 BitsPerSample;
};

struct FMT_BLOCK_DEF
{
	s8 fmt_id[4];    // 'f','m','t',' '
	u32 fmt_size;
	struct WAVE_FORMAT_DEF wav_format;
};
#endif
/*
WAV�ļ���ʽ
------------------------------------------------
	|             RIFF WAVE Chunk                  |
	|             ID  = 'RIFF'                     |
	|             RiffType = 'WAVE'                |
	------------------------------------------------
	|             Format Chunk                     |
	|             ID = 'fmt '                      |
	------------------------------------------------
	|             Fact Chunk(optional)             |
	|             ID = 'fact'                      |
	------------------------------------------------
	|             Data Chunk                       |
	|             ID = 'data'                      |
	------------------------------------------------
	ͼ1   Wav��ʽ����Chunkʾ�� 

	���г���Fact Chunk�⣬��������Chunk�Ǳ���ġ�ÿ��Chunk�и��Ե�ID��λ��Chunk�ʼλ�ã�
	��Ϊ��ʾ�����Ҿ�Ϊ4���ֽڡ����ҽ�����ID�������Chunk��С��ȥ��ID��Size��ռ���ֽ�����ʣ��
	�������ֽ���Ŀ����4���ֽڱ�ʾ�����ֽڱ�ʾ��ֵ��λ�����ֽڱ�ʾ��ֵ��λ�����������ܸ���Chunk���ݡ�
	PS��
	������ֵ��ʾ��Ϊ���ֽڱ�ʾ��λ�����ֽڱ�ʾ��λ�� 

	2���������
	RIFF WAVE Chunk
	==================================
	|       |��ռ�ֽ���|  ��������   |
	==================================
	| ID    |  4 Bytes |   'RIFF'    |
	----------------------------------
	| Size  |  4 Bytes |             |
	----------------------------------
	| Type  |  4 Bytes |   'WAVE'    |
	----------------------------------
	ͼ2  RIFF WAVE Chunk 

	��'FIFF'��Ϊ��ʾ��Ȼ�������Ϊsize�ֶΣ���size������wav�ļ���С��ȥID��Size��ռ�õ��ֽ�����
	��FileLen - 8 = Size��Ȼ����Type�ֶΣ�Ϊ'WAVE'����ʾ��wav�ļ���



	Format Chunk
	====================================================================
	|               |   �ֽ���  |              ��������                |
	====================================================================
	| ID            |  4 Bytes  |   'fmt '                             |
	--------------------------------------------------------------------
	| Size          |  4 Bytes  | ��ֵΪ16��18��18������ָ�����Ϣ     |
	--------------------------------------------------------------------  ----
	| FormatTag     |  2 Bytes  | ���뷽ʽ��һ��Ϊ0x0001               |     |
	--------------------------------------------------------------------     |
	| Channels      |  2 Bytes  | ������Ŀ��1--��������2--˫����       |     |
	--------------------------------------------------------------------     |
	| SamplesPerSec |  4 Bytes  | ����Ƶ��                             |     |
	--------------------------------------------------------------------     |
	| AvgBytesPerSec|  4 Bytes  | ÿ�������ֽ���                       |     |===> WAVE_FORMAT
	--------------------------------------------------------------------     |
	| BlockAlign    |  2 Bytes  | ���ݿ���뵥λ(ÿ��������Ҫ���ֽ���) |     |
	--------------------------------------------------------------------     |
	| BitsPerSample |  2 Bytes  | ÿ��������Ҫ��bit��                  |     |
	--------------------------------------------------------------------     |
	|               |  2 Bytes  | ������Ϣ����ѡ��ͨ��Size���ж����ޣ� |     |
	--------------------------------------------------------------------  ----
	ͼ3  Format Chunk 

	��'fmt '��Ϊ��ʾ��һ�������SizeΪ16����ʱ��󸽼���Ϣû�У�
	���Ϊ18����������2���ֽڵĸ�����Ϣ����Ҫ��һЩ�����Ƴɵ�wav��ʽ�к��и�2���ֽڵĸ�����Ϣ��

	Fact Chunk
	==================================
	|       |��ռ�ֽ���|  ��������   |
	==================================
	| ID    |  4 Bytes |   'fact'    |
	----------------------------------
	| Size  |  4 Bytes |   ��ֵΪ4   |
	----------------------------------
	| data  |  4 Bytes |             |
	----------------------------------
	ͼ4  Fact Chunk 

	Fact Chunk�ǿ�ѡ�ֶΣ�һ�㵱wav�ļ���ĳЩ����ת�����ɣ��������Chunk��


	Data Chunk
	==================================
	|       |��ռ�ֽ���|  ��������   |
	==================================
	| ID    |  4 Bytes |   'data'    |
	----------------------------------
	| Size  |  4 Bytes |             |
	----------------------------------
	| data  |          |             |
	----------------------------------
	ͼ5 Data Chunk 

	Data Chunk����������wav���ݵĵط�����'data'��Ϊ��Chunk�ı�ʾ��Ȼ�������ݵĴ�С��
	�����ž���wav���ݡ�����Format Chunk�е��������Լ�����bit����wav���ݵ�bitλ�ÿ��Էֳ����¼�����ʽ��
	---------------------------------------------------------------------
	|   ������  |    ȡ��1    |    ȡ��2    |    ȡ��3    |    ȡ��4    |
	|           |--------------------------------------------------------
	|  8bit���� |    ����0    |    ����0    |    ����0    |    ����0    |
	---------------------------------------------------------------------
	|   ˫����  |          ȡ��1            |           ȡ��2           |
	|           |--------------------------------------------------------
	|  8bit���� |  ����0(��)  |  ����1(��)  |  ����0(��)  |  ����1(��)  |
	---------------------------------------------------------------------
	|           |          ȡ��1            |           ȡ��2           |
	|   ������  |--------------------------------------------------------
	| 16bit���� |    ����0    |  ����0      |    ����0    |  ����0      |
	|           | (��λ�ֽ�)  | (��λ�ֽ�)  | (��λ�ֽ�)  | (��λ�ֽ�)  |
	---------------------------------------------------------------------
	|           |                         ȡ��1                         |
	|   ˫����  |--------------------------------------------------------
	| 16bit���� |  ����0(��)  |  ����0(��)  |  ����1(��)  |  ����1(��)  |
	|           | (��λ�ֽ�)  | (��λ�ֽ�)  | (��λ�ֽ�)  | (��λ�ֽ�)  |
	---------------------------------------------------------------------
	ͼ6 wav����bitλ�ð��ŷ�ʽ 

*/