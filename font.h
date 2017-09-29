const unsigned char font8x16[10][16] = {
  { B00111100,
    B01111110,
    B11100111,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  },
  { B00000011,
    B00000111,
    B00001111,
    B00011111,
    B00111011,
    B01110011,
    B11100011,
    B11000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011
  },
  { B00111100,
    B01111110,
    B11100111,
    B11000011,
    B00000011,
    B00000011,
    B00000011,
    B00000111,
    B00001110,
    B00011100,
    B00111000,
    B01110000,
    B11100000,
    B11000000,
    B11111111,
    B11111111
  },
  { B00111100,
    B01111110,
    B11100111,
    B11000011,
    B00000011,
    B00000111,
    B00001110,
    B00111100,
    B00111100,
    B00001110,
    B00000111,
    B00000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  },
  { B00000011,
    B00000111,
    B00001110,
    B00011100,
    B00111000,
    B01110000,
    B11100000,
    B11000000,
    B11000000,
    B11111111,
    B01111111,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B00000011
  },
  { B11111111,
    B11111111,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11111100,
    B11111110,
    B00000111,
    B00000011,
    B00000011,
    B00000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  },
  { B00111100,
    B01111110,
    B11100111,
    B11000011,
    B11000000,
    B11000000,
    B11000000,
    B11111100,
    B11111110,
    B11100111,
    B11000011,
    B11000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  },
  { B11111111,
    B11111111,
    B11000011,
    B11000111,
    B00000110,
    B00001110,
    B00001100,
    B00011100,
    B00011000,
    B00111000,
    B00110000,
    B01110000,
    B01100000,
    B11100000,
    B11000000,
    B11000000
  },
  { B00111100,
    B01111110,
    B11100111,
    B11000011,
    B11000011,
    B11000011,
    B11100111,
    B01111110,
    B01111110,
    B11100111,
    B11000011,
    B11000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  },
  { B00111100,
    B01111110,
    B11100111,
    B11000011,
    B11000011,
    B11000011,
    B11100111,
    B01111111,
    B00111111,
    B00000011,
    B00000011,
    B00000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  }
};

const unsigned char font5x7[96][7] = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // 0x20, Space
  {0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04},   // 0x21, !
  {0x09, 0x09, 0x12, 0x00, 0x00, 0x00, 0x00},   // 0x22, "
  {0x0a, 0x0a, 0x1f, 0x0a, 0x1f, 0x0a, 0x0a},   // 0x23, #
  {0x04, 0x0f, 0x14, 0x0e, 0x05, 0x1e, 0x04},   // 0x24, $
  {0x19, 0x19, 0x02, 0x04, 0x08, 0x13, 0x13},   // 0x25, %
  {0x04, 0x0a, 0x0a, 0x0a, 0x15, 0x12, 0x0d},   // 0x26, &
  {0x04, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00},   // 0x27, '
  {0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02},   // 0x28, (
  {0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08},   // 0x29, )
  {0x04, 0x15, 0x0e, 0x1f, 0x0e, 0x15, 0x04},   // 0x2a, *
  {0x00, 0x04, 0x04, 0x1f, 0x04, 0x04, 0x00},   // 0x2b, +
  {0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x08},   // 0x2c, ,
  {0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00},   // 0x2d, -
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c},   // 0x2e, .
  {0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10},   // 0x2f, /
  {0x0e, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0e},   // 0x30, 0
  {0x04, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x0e},   // 0x31, 1
  {0x0e, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1f},   // 0x32, 2
  {0x0e, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0e},   // 0x33, 3
  {0x02, 0x06, 0x0a, 0x12, 0x1f, 0x02, 0x02},   // 0x34, 4
  {0x1f, 0x10, 0x1e, 0x01, 0x01, 0x11, 0x0e},   // 0x35, 5
  {0x06, 0x08, 0x10, 0x1e, 0x11, 0x11, 0x0e},   // 0x36, 6
  {0x1f, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08},   // 0x37, 7
  {0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e},   // 0x38, 8
  {0x0e, 0x11, 0x11, 0x0f, 0x01, 0x02, 0x0c},   // 0x39, 9
  {0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00},   // 0x3a, :
  {0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x04, 0x08},   // 0x3b, ;
  {0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02},   // 0x3c, <
  {0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00},   // 0x3d, =
  {0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08},   // 0x3e, >
  {0x0e, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04},   // 0x3f, ?
  {0x0e, 0x11, 0x17, 0x15, 0x17, 0x10, 0x0f},   // 0x40, @
  {0x04, 0x0a, 0x11, 0x11, 0x1f, 0x11, 0x11},   // 0x41, A
  {0x1e, 0x11, 0x11, 0x1e, 0x11, 0x11, 0x1e},   // 0x42, B
  {0x0e, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0e},   // 0x43, C
  {0x1e, 0x09, 0x09, 0x09, 0x09, 0x09, 0x1e},   // 0x44, D
  {0x1f, 0x10, 0x10, 0x1c, 0x10, 0x10, 0x1f},   // 0x45, E
  {0x1f, 0x10, 0x10, 0x1f, 0x10, 0x10, 0x10},   // 0x46, F
  {0x0e, 0x11, 0x10, 0x10, 0x13, 0x11, 0x0f},   // 0x37, G
  {0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11},   // 0x48, H
  {0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e},   // 0x49, I
  {0x1f, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0c},   // 0x4a, J
  {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11},   // 0x4b, K
  {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f},   // 0x4c, L
  {0x11, 0x1b, 0x15, 0x11, 0x11, 0x11, 0x11},   // 0x4d, M
  {0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11},   // 0x4e, N
  {0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e},   // 0x4f, O
  {0x1e, 0x11, 0x11, 0x1e, 0x10, 0x10, 0x10},   // 0x50, P
  {0x0e, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0d},   // 0x51, Q
  {0x1e, 0x11, 0x11, 0x1e, 0x14, 0x12, 0x11},   // 0x52, R
  {0x0e, 0x11, 0x10, 0x0e, 0x01, 0x11, 0x0e},   // 0x53, S
  {0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},   // 0x54, T
  {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e},   // 0x55, U
  {0x11, 0x11, 0x11, 0x11, 0x11, 0x0a, 0x04},   // 0x56, V
  {0x11, 0x11, 0x11, 0x15, 0x15, 0x1b, 0x11},   // 0x57, W
  {0x11, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x11},   // 0x58, X
  {0x11, 0x11, 0x0a, 0x04, 0x04, 0x04, 0x04},   // 0x59, Y
  {0x1f, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1f},   // 0x5a, Z
  {0x0e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0e},   // 0x5b, [
  {0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01},   // 0x5c, \ 
  {0x0e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0e},   // 0x5d, ]
  {0x04, 0x0a, 0x11, 0x00, 0x00, 0x00, 0x00},   // 0x5e, ^
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f},   // 0x5f, _
  {0x04, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00},   // 0x60, `
  {0x00, 0x0e, 0x01, 0x0d, 0x13, 0x13, 0x0d},   // 0x61, a
  {0x10, 0x10, 0x10, 0x1c, 0x12, 0x12, 0x1c},   // 0x62, b
  {0x00, 0x00, 0x00, 0x0e, 0x10, 0x10, 0x0e},   // 0x63, c
  {0x01, 0x01, 0x01, 0x07, 0x09, 0x09, 0x07},   // 0x64, d
  {0x00, 0x00, 0x0e, 0x11, 0x1f, 0x10, 0x0f},   // 0x65, e
  {0x06, 0x09, 0x08, 0x1c, 0x08, 0x08, 0x08},   // 0x66, f
  {0x0e, 0x11, 0x13, 0x0d, 0x01, 0x01, 0x0e},   // 0x67, g
  {0x10, 0x10, 0x10, 0x16, 0x19, 0x11, 0x11},   // 0x68, h
  {0x00, 0x04, 0x00, 0x0c, 0x04, 0x04, 0x0e},   // 0x69, i
  {0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0c},   // 0x6a, j
  {0x10, 0x10, 0x12, 0x14, 0x18, 0x14, 0x12},   // 0x6b, k
  {0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},   // 0x6c, l
  {0x00, 0x00, 0x0a, 0x15, 0x15, 0x11, 0x11},   // 0x6d, m
  {0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11},   // 0x6e, n
  {0x00, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e},   // 0x6f, o
  {0x00, 0x1c, 0x12, 0x12, 0x1c, 0x10, 0x10},   // 0x70, p
  {0x00, 0x07, 0x09, 0x09, 0x07, 0x01, 0x01},   // 0x71, q
  {0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10},   // 0x72, r
  {0x00, 0x00, 0x0f, 0x10, 0x0e, 0x01, 0x1e},   // 0x73, s
  {0x08, 0x08, 0x1c, 0x08, 0x08, 0x09, 0x06},   // 0x74, t
  {0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0d},   // 0x75, u
  {0x00, 0x00, 0x11, 0x11, 0x11, 0x0a, 0x04},   // 0x76, v
  {0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0a},   // 0x77, w
  {0x00, 0x00, 0x11, 0x0a, 0x04, 0x0a, 0x11},   // 0x78, x
  {0x00, 0x11, 0x11, 0x0f, 0x01, 0x11, 0x0e},   // 0x79, y
  {0x00, 0x00, 0x1f, 0x02, 0x04, 0x08, 0x1f},   // 0x7a, z
  {0x06, 0x08, 0x08, 0x10, 0x08, 0x08, 0x06},   // 0x7b, {
  {0x04, 0x04, 0x04, 0x00, 0x04, 0x04, 0x04},   // 0x7c, |
  {0x0c, 0x02, 0x02, 0x01, 0x02, 0x02, 0x0c},   // 0x7d, }
  {0x08, 0x15, 0x02, 0x00, 0x00, 0x00, 0x00},   // 0x7e, ~
  {0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}    // 0x7f, DEL
};

