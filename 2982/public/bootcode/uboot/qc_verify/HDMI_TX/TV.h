#ifndef _TV_REG_H_INCLUDED_
#define _TV_REG_H_INCLUDED_

void TV_525i(UINT32	colorbar, UINT32 RGB_mode, UINT32 video_format);
void TV_1080_50i(UINT32 colorbar);
void TV_1080_60i(UINT32 colorbar);
void TV_1080_24p(UINT32 colorbar);
void TV_525p(UINT32 colorbar);
void TV_625i(UINT32 colorbar, UINT32 RGB_mode);
void TV_625p(UINT32 colorbar);
void TV_720p_50(UINT32 colorbar);
void TV_720p_60(UINT32 colorbar);
void TV_1080p_50(void);
void TV_1080p_60(void);
#endif