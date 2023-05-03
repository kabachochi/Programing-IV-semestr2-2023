#include "coder.h"

int encode(uint32_t code_point, CodeUnits *code_units)
{
    if (code_point < 0x80) // 1000 0000
    {
        code_units->length = 1;
        code_units->code[0] = code_point;
    }
    else if (code_point < 0x800) // 1000 0000 0000
    {
        code_units->length = 2;
        code_units->code[0] = 0xC0 | (code_point >> 6); // 1100 0000
        code_units->code[1] = 0x80 | (code_point & 0x3F); // 1000 0000 | 0011 1111
    }
    else if (code_point < 0x10000) // 0001 0000 0000 0000 0000
    {
        code_units->length = 3;
        code_units->code[0] = 0xE0 | (code_point >> 12); // 1110 0000
        code_units->code[1] = 0x80 | ((code_point >> 6) & 0x3F); // 1000 0000 | 0011 1111
        code_units->code[2] = 0x80 | (code_point & 0x3F); // 1000 0000 | 0011 1111
    }
    else if (code_point < 0x200000) // 0010 0000 0000 0000 0000 0000
    {
        code_units->length = 4;
        code_units->code[0] = 0xF0 | (code_point >> 18); // 1111 0000
        code_units->code[1] = 0x80 | ((code_point >> 12) & 0x3F); // 1000 0000 | 0011 1111
        code_units->code[2] = 0x80 | ((code_point >> 6) & 0x3F); // 1000 0000 | 0011 1111
        code_units->code[3] = 0x80 | (code_point & 0x3F); // 1000 0000 | 0011 1111
    }
    else
    {
        return -1;
    }
    return 0;
}

uint32_t decode(const CodeUnits *code_unit)
{
    uint32_t result = 0;
    if (code_unit->length == 1)
    {
        result = code_unit->code[0];
    }
    else if (code_unit->length == 2 && code_unit->code[0] <= 0xDF)
    {
        result = code_unit->code[0] & 0x1F;
        result = (result << 6) | (code_unit->code[1] & 0x3F);
    }
    else if (code_unit->length == 3 && code_unit->code[0] <= 0xEF)
    {
        result = code_unit->code[0] & 0xF;
        result = (result << 6) | (code_unit->code[1] & 0x3F);
        result = (result << 6) | (code_unit->code[2] & 0x3F);
    }
    else if(code_unit->length == 4 && code_unit->code[0] <= 0xF7)
    {
        result = code_unit->code[0] & 0x7;
        result = (result << 6) | (code_unit->code[1] & 0x3F);
        result = (result << 6) | (code_unit->code[2] & 0x3F);
        result = (result << 6) | (code_unit->code[3] & 0x3F);
    }
    return result;
}

int read_next_code_unit(FILE *in, CodeUnits *code_units)
{
	uint8_t buffer = 0;
	fread(&buffer, 1, 1, in);
	while(!feof(in)) 
    {
		uint8_t cur_byte = 0;
		while(buffer & (1 << (7 - cur_byte))) 
        {
			cur_byte++;
		}
		if (cur_byte == 1) 
        {
			fread(&buffer, 1, 1, in);
			continue;
		}
		if (cur_byte == 0) 
        {
			cur_byte = 1;
		}
		if (cur_byte <= MaxCodeLength) 
        {
			code_units->length = 0;
			for (int i = 0; i < cur_byte; i++) 
            {
				code_units->code[i] = buffer;
				code_units->length++;
				if ((i + 1) == cur_byte) 
                {
					return 0;
				}
				fread(&buffer, 1, 1, in);
				if ((buffer & 0xC0) != 0x80) 
                {
					break;
				}
			}
		}
	}
	return -1;
}

int write_code_unit(FILE *out, const CodeUnits *code_unit)
{
    int result = fwrite(code_unit->code, 1, code_unit->length, out);
    return result;
}