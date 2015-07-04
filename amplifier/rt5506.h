/*
 * Copyright (C) 2015, The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define RT5506_DEVICE "/dev/rt5506"
#define RT5506_MAX_REG_DATA 15

struct rt5506_reg_data {
    unsigned char addr;
    unsigned char val;
};

struct rt5506_config {
    unsigned int reg_len;
    struct rt5506_reg_data reg[RT5506_MAX_REG_DATA];
};

struct rt5506_comm_data {
    unsigned int out_mode;
    struct rt5506_config config;
};

static struct rt5506_reg_data rt5506_playback_data[] = {
    { 0x00, 0xC0, },
    { 0x01, 0x1B, }, // gain -1dB
    { 0x02, 0x80, }, // noise gate on
    { 0x08, 0x37, }, // noise gate on
    { 0x07, 0x7F, }, // noise gate setting
    { 0x09, 0x02, }, // noise gate setting
    { 0x0A, 0x03, }, // noise gate setting
    { 0x0B, 0xD9, }, // noise gate setting
};

static struct rt5506_reg_data rt5506_playback_128_data[] = {
    { 0x00, 0xC0, },
    { 0x01, 0x20, }, // gain 4dB
    { 0x02, 0x80, }, // noise gate on
    { 0x08, 0x37, }, // noise gate on
    { 0x07, 0x7F, }, // noise gate setting
    { 0x09, 0x02, }, // noise gate setting
    { 0x0A, 0x03, }, // noise gate setting
    { 0x0B, 0xD9, }, // noise gate setting
};

static struct rt5506_reg_data rt5506_ring_data[] = {
    { 0x00, 0xC0, },
    { 0x01, 0x1C, }, // gain 0dB
    { 0x02, 0x81, }, // noise gate on
    { 0x08, 0x01, }, // noise gate on
    { 0x07, 0x7F, }, // noise gate setting
    { 0x09, 0x01, }, // noise gate setting
    { 0x0A, 0x00, }, // noise gate setting
    { 0x0B, 0xC7, }, // noise gate setting
};

static struct rt5506_reg_data rt5506_voice_data[] = {
    { 0x00, 0xC0, },
    { 0x01, 0x1C, }, // gain 0dB
    { 0x02, 0x00, }, // noise gate off
    { 0x07, 0x7F, }, // noise gate setting
    { 0x09, 0x01, }, // noise gate setting
    { 0x0A, 0x00, }, // noise gate setting
    { 0x0B, 0xC7, }, // noise gate setting
};

enum {
    AMP_INIT = 0,
    AMP_MUTE,
    AMP_MAX_FUNC
};

enum PLAYBACK_MODE {
    PLAYBACK_MODE_OFF = AMP_MAX_FUNC,
    PLAYBACK_MODE_PLAYBACK,
    PLAYBACK_MODE_PLAYBACK8OH,
    PLAYBACK_MODE_PLAYBACK16OH,
    PLAYBACK_MODE_PLAYBACK32OH,
    PLAYBACK_MODE_PLAYBACK64OH,
    PLAYBACK_MODE_PLAYBACK128OH,
    PLAYBACK_MODE_PLAYBACK256OH,
    PLAYBACK_MODE_PLAYBACK500OH,
    PLAYBACK_MODE_PLAYBACK1KOH,
    PLAYBACK_MODE_VOICE,
    PLAYBACK_MODE_TTY,
    PLAYBACK_MODE_FM,
    PLAYBACK_MODE_RING,
    PLAYBACK_MODE_MFG,
    PLAYBACK_MODE_BEATS_8_64,
    PLAYBACK_MODE_BEATS_128_500,
    PLAYBACK_MODE_MONO,
    PLAYBACK_MODE_MONO_BEATS,
    PLAYBACK_MAX_MODE
};

enum HEADSET_OM {
    HEADSET_8OM = 0,
    HEADSET_16OM,
    HEADSET_32OM,
    HEADSET_64OM,
    HEADSET_128OM,
    HEADSET_256OM,
    HEADSET_500OM,
    HEADSET_1KOM,
    HEADSET_MONO,
    HEADSET_OM_UNDER_DETECT,
};

#define AMP_IOCTL_MAGIC 'g'
#define AMP_SET_CONFIG   _IOW(AMP_IOCTL_MAGIC, 0x01,  unsigned)
#define AMP_READ_CONFIG  _IOW(AMP_IOCTL_MAGIC, 0x02, unsigned)
#define AMP_SET_MODE        _IOW(AMP_IOCTL_MAGIC, 0x03, unsigned)
#define AMP_SET_PARAM       _IOW(AMP_IOCTL_MAGIC, 0x04,  unsigned)
#define AMP_WRITE_REG       _IOW(AMP_IOCTL_MAGIC, 0x07,  unsigned)
#define AMP_QUERY_OM       _IOW(AMP_IOCTL_MAGIC, 0x08,  unsigned)

int rt5506_set_mode(audio_mode_t mode);