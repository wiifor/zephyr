static const q15_t in_q15[256] = {
    0x509E, 0x6248, 0x3409, 0x5E56, 0x0272, 0x213A, 0x0212, 0x7F15,
    0x379C, 0x3EE7, 0x1167, 0x60C0, 0x483C, 0x4337, 0x3703, 0x66EB,
    0x6DF6, 0x672B, 0x38B0, 0x0E04, 0x4334, 0x3322, 0x39E8, 0x0623,
    0x6E58, 0x1F35, 0x7C15, 0x49AF, 0x456D, 0x505F, 0x0285, 0x7AED,
    0x50B0, 0x0C7F, 0x06A7, 0x59E7, 0x196C, 0x1374, 0x102B, 0x5790,
    0x5138, 0x0882, 0x2415, 0x77A8, 0x43B9, 0x0119, 0x605D, 0x6C9F,
    0x6D9B, 0x6AD8, 0x6416, 0x382C, 0x3358, 0x3019, 0x163A, 0x663C,
    0x4A55, 0x2CF4, 0x4D71, 0x11D6, 0x5BF6, 0x5AD6, 0x5163, 0x3ABE,
    0x5B3A, 0x1957, 0x1304, 0x4CAF, 0x1393, 0x2AD5, 0x4465, 0x2B8D,
    0x725B, 0x6C3E, 0x0758, 0x3479, 0x6A6E, 0x2C1C, 0x39BD, 0x5C35,
    0x5F21, 0x3265, 0x503C, 0x7995, 0x5CF9, 0x1B11, 0x4754, 0x28B9,
    0x1EF1, 0x3689, 0x0E7F, 0x4B33, 0x3CF1, 0x4A43, 0x2314, 0x10A3,
    0x1D7D, 0x0D6E, 0x056E, 0x3ADA, 0x321F, 0x1C30, 0x2CF2, 0x270E,
    0x6187, 0x6814, 0x580D, 0x6C91, 0x2EAE, 0x441B, 0x08FD, 0x6A92,
    0x5D18, 0x14E8, 0x014B, 0x1968, 0x51DA, 0x645C, 0x7F22, 0x3357,
    0x3840, 0x0B87, 0x40C0, 0x3DCF, 0x3DDF, 0x32A5, 0x7169, 0x253C,
    0x2CB2, 0x102E, 0x0D30, 0x3FC5, 0x4F12, 0x5A2E, 0x1364, 0x0C6F,
    0x6C28, 0x7C87, 0x720C, 0x11FC, 0x5E03, 0x0744, 0x0CAC, 0x7BDE,
    0x5B94, 0x4CFC, 0x299B, 0x3D78, 0x73CE, 0x42AD, 0x001F, 0x4C9D,
    0x33C4, 0x6E1C, 0x09B5, 0x0D80, 0x1C46, 0x420C, 0x5BCF, 0x0872,
    0x4B81, 0x559C, 0x7534, 0x1A22, 0x6CD2, 0x7FFF, 0x65E7, 0x4ECA,
    0x1F3F, 0x729C, 0x3DC6, 0x7E7F, 0x5E25, 0x5477, 0x22A0, 0x20B9,
    0x2505, 0x5170, 0x1A86, 0x4DC2, 0x4DBE, 0x3AE4, 0x1FA4, 0x5A46,
    0x7C96, 0x71BC, 0x32AE, 0x18E6, 0x373A, 0x52C7, 0x13E7, 0x0D29,
    0x433C, 0x346C, 0x0FD3, 0x3E88, 0x43D3, 0x0F6B, 0x460F, 0x4378,
    0x3E64, 0x26C8, 0x5520, 0x69C7, 0x402D, 0x2D95, 0x4D6D, 0x22C0,
    0x2315, 0x1B79, 0x296F, 0x6A3E, 0x7369, 0x4F2F, 0x7F87, 0x2B08,
    0x4BCA, 0x1CAA, 0x51E1, 0x0696, 0x2517, 0x2B3F, 0x6F4E, 0x4DF1,
    0x0B9A, 0x32D7, 0x1C63, 0x314C, 0x3D8E, 0x03C4, 0x45E5, 0x44CC,
    0x2059, 0x0EF9, 0x58FC, 0x431B, 0x7808, 0x3E0F, 0x79C0, 0x4202,
    0x44AF, 0x6541, 0x25DF, 0x1A7E, 0x049B, 0x68DF, 0x2748, 0x62FD,
    0x6FCD, 0x2D02, 0x5E82, 0x4580, 0x17EB, 0x4FF7, 0x0CB5, 0x5169
    };

static const uint32_t ref_f32[256] = {
    0x3f213b11, 0x3f4490f0, 0x3ed022a5, 0x3f3cab38,
    0x3c9c623b, 0x3e84e6a0, 0x3c846a11, 0x3f7e2976,
    0x3ede70cd, 0x3efb9d15, 0x3e0b3adb, 0x3f417f13,
    0x3f10784a, 0x3f066e9f, 0x3edc0ca0, 0x3f4dd6a2,
    0x3f5bec28, 0x3f4e5658, 0x3ee2c1ec, 0x3de03e2e,
    0x3f0668b9, 0x3ecc89e2, 0x3ee79e24, 0x3d445dee,
    0x3f5caffa, 0x3e79a59e, 0x3f782afe, 0x3f135e59,
    0x3f0ad91d, 0x3f20be4b, 0x3ca120ab, 0x3f75d9e6,
    0x3f215f01, 0x3dc7ec29, 0x3d54e122, 0x3f33cd07,
    0x3e4b5e00, 0x3e1ba166, 0x3e015850, 0x3f2f2052,
    0x3f2270a4, 0x3d882386, 0x3e905236, 0x3f6f501a,
    0x3f077239, 0x3c0c6e1a, 0x3f40b9d3, 0x3f593de1,
    0x3f5b363a, 0x3f55b04c, 0x3f482b0e, 0x3ee0b1e2,
    0x3ecd6052, 0x3ec0630f, 0x3e31cfba, 0x3f4c77c2,
    0x3f14a9b0, 0x3eb3d06d, 0x3f1ae140, 0x3e0eb2f8,
    0x3f37ebd2, 0x3f35ab2a, 0x3f22c520, 0x3eeaf6ac,
    0x3f3673c0, 0x3e4ab831, 0x3e1820b0, 0x3f195ec1,
    0x3e1c96df, 0x3eab551d, 0x3f08ca4f, 0x3eae3497,
    0x3f64b63d, 0x3f587c9c, 0x3d6afb7d, 0x3ed1e212,
    0x3f54dc04, 0x3eb070ba, 0x3ee6f495, 0x3f386ac8,
    0x3f3e42f5, 0x3ec9953c, 0x3f20770d, 0x3f732ab1,
    0x3f39f1bd, 0x3e588502, 0x3f0ea706, 0x3ea2e3aa,
    0x3e778a40, 0x3eda2252, 0x3de7f263, 0x3f1666f1,
    0x3ef3c54f, 0x3f1485e3, 0x3e8c50ce, 0x3e051a41,
    0x3e6be92a, 0x3dd6e5f3, 0x3d2db055, 0x3eeb6724,
    0x3ec87ad9, 0x3e618265, 0x3eb3c6be, 0x3e9c38af,
    0x3f430d25, 0x3f502887, 0x3f301996, 0x3f5922fd,
    0x3ebab964, 0x3f083661, 0x3d8fca01, 0x3f55238d,
    0x3f3a2f52, 0x3e273ea4, 0x3c25715c, 0x3e4b3f18,
    0x3f23b4e6, 0x3f48b7c1, 0x3f7e430c, 0x3ecd5a53,
    0x3ee0ffe7, 0x3db87386, 0x3f017f9f, 0x3ef73b34,
    0x3ef77cc0, 0x3eca9482, 0x3f62d12b, 0x3e94f050,
    0x3eb2c8cd, 0x3e01731a, 0x3dd30076, 0x3eff1502,
    0x3f1e2321, 0x3f345cf1, 0x3e1b1f35, 0x3dc6f018,
    0x3f58505c, 0x3f790d8b, 0x3f641754, 0x3e0fe121,
    0x3f3c05ba, 0x3d688015, 0x3dcabcef, 0x3f77bb8f,
    0x3f3727b3, 0x3f19f88f, 0x3ea66a54, 0x3ef5de04,
    0x3f679b2d, 0x3f055aba, 0x3a78f30a, 0x3f193a3c,
    0x3ecf0f70, 0x3f5c3797, 0x3d9b543f, 0x3dd8067d,
    0x3e622ca9, 0x3f0417b7, 0x3f379dd4, 0x3d871ef5,
    0x3f170259, 0x3f2b381e, 0x3f6a6720, 0x3e5112b9,
    0x3f59a367, 0x3f800000, 0x3f4bceb4, 0x3f1d9359,
    0x3e79fbfd, 0x3f6537c6, 0x3ef71827, 0x3f7cfedf,
    0x3f3c4996, 0x3f28ed26, 0x3e8a7e11, 0x3e82e570,
    0x3e9413aa, 0x3f22dfd6, 0x3e543391, 0x3f1b833b,
    0x3f1b7c3c, 0x3eeb8f3b, 0x3e7d1ed9, 0x3f348bf2,
    0x3f792b4f, 0x3f637719, 0x3ecab795, 0x3e47314c,
    0x3edce760, 0x3f258d8c, 0x3e1f3948, 0x3dd292f7,
    0x3f067713, 0x3ed1ae5b, 0x3dfd32ad, 0x3efa1e3d,
    0x3f07a52f, 0x3df6b293, 0x3f0c1d36, 0x3f06efbe,
    0x3ef990cb, 0x3e9b2019, 0x3f2a3f89, 0x3f538d5c,
    0x3f0059fd, 0x3eb65225, 0x3f1ad974, 0x3e8aff06,
    0x3e8c52e2, 0x3e5bc626, 0x3ea5bd61, 0x3f547b87,
    0x3f66d279, 0x3f1e5ec3, 0x3f7f0d9f, 0x3eac1eac,
    0x3f179378, 0x3e654c34, 0x3f23c1eb, 0x3d52bf9f,
    0x3e945a14, 0x3eacfbe9, 0x3f5e9c85, 0x3f1be283,
    0x3db99bcb, 0x3ecb5cda, 0x3e631a5c, 0x3ec5311b,
    0x3ef6397e, 0x3cf0e8f1, 0x3f0bc95c, 0x3f09974c,
    0x3e8162d3, 0x3def9555, 0x3f31f82e, 0x3f0636a9,
    0x3f7010bb, 0x3ef83a58, 0x3f737ffb, 0x3f04041a,
    0x3f095ec8, 0x3f4a81d2, 0x3e977d2d, 0x3e53f3b0,
    0x3d135320, 0x3f51bde2, 0x3e9d1e1a, 0x3f45f927,
    0x3f5f9a61, 0x3eb4096f, 0x3f3d0372, 0x3f0b00fd,
    0x3e3f59b7, 0x3f1fee89, 0x3dcb4956, 0x3f22d2e4
    };

static const q31_t ref_q31[256] = {
    0x509D8862, 0x624877F7, 0x3408A948, 0x5E559BCB,
    0x027188EE, 0x2139A800, 0x0211A843, 0x7F14BADC,
    0x379C332F, 0x3EE7452C, 0x11675B51, 0x60BF89AF,
    0x483C2511, 0x43374F66, 0x370327E5, 0x66EB511A,
    0x6DF61417, 0x672B2C23, 0x38B07AE8, 0x0E03E2DB,
    0x43345C6E, 0x3322787B, 0x39E7890F, 0x0622EF73,
    0x6E57FD00, 0x1F34B3CC, 0x7C157EC1, 0x49AF2C47,
    0x456C8EBC, 0x505F256F, 0x028482AC, 0x7AECF334,
    0x50AF80B4, 0x0C7EC295, 0x06A70910, 0x59E6834D,
    0x196BC00C, 0x13742CB2, 0x102B09FC, 0x57902935,
    0x513851DD, 0x08823859, 0x24148D8D, 0x77A80CE6,
    0x43B91C67, 0x0118DC34, 0x605CE9B1, 0x6C9EF0A6,
    0x6D9B1D30, 0x6AD825D1, 0x641586E9, 0x382C7879,
    0x33581471, 0x3018C3BF, 0x1639F73A, 0x663BE0C7,
    0x4A54D7F5, 0x2CF41B52, 0x4D70A003, 0x11D65EF9,
    0x5BF5E93A, 0x5AD59505, 0x51628FF3, 0x3ABDAAF8,
    0x5B39E03A, 0x19570619, 0x13041607, 0x4CAF60BB,
    0x1392DBED, 0x2AD5475D, 0x4465276C, 0x2B8D25A6,
    0x725B1EAE, 0x6C3E4DD1, 0x0757DBE7, 0x3478848B,
    0x6A6E023D, 0x2C1C2E96, 0x39BD254D, 0x5C3563F0,
    0x5F217A75, 0x32654EE3, 0x503B867A, 0x799558BC,
    0x5CF8DE97, 0x1B10A044, 0x475382F4, 0x28B8EA6C,
    0x1EF147F1, 0x3688948E, 0x0E7F262A, 0x4B33788E,
    0x3CF153AE, 0x4A42F199, 0x2314336B, 0x10A34829,
    0x1D7D2538, 0x0D6E5F31, 0x056D82AB, 0x3AD9C90E,
    0x321EB627, 0x1C304CA4, 0x2CF1AF64, 0x270E2BDF,
    0x61869260, 0x681443A8, 0x580CCADC, 0x6C917EAB,
    0x2EAE58F5, 0x441B30AE, 0x08FCA015, 0x6A91C6BB,
    0x5D17A91C, 0x14E7D470, 0x014AE2B9, 0x1967E301,
    0x51DA72CA, 0x645BE0B5, 0x7F218621, 0x335694C6,
    0x383FF9DE, 0x0B873866, 0x40BFCFA1, 0x3DCECD08,
    0x3DDF301F, 0x32A52079, 0x716895B8, 0x253C1411,
    0x2CB23360, 0x102E6345, 0x0D30075F, 0x3FC54088,
    0x4F119072, 0x5A2E78AC, 0x1363E693, 0x0C6F017B,
    0x6C282E06, 0x7C86C547, 0x720BAA1B, 0x11FC2411,
    0x5E02DCD9, 0x074400A7, 0x0CABCEE8, 0x7BDDC793,
    0x5B93D962, 0x4CFC47B9, 0x299A9515, 0x3D7780EA,
    0x73CD96AA, 0x42AD5D0D, 0x001F1E61, 0x4C9D1DD8,
    0x33C3DC1F, 0x6E1BCBA5, 0x09B543F3, 0x0D8067D5,
    0x1C459519, 0x420BDB61, 0x5BCEEA33, 0x0871EF49,
    0x4B812C68, 0x559C0EE8, 0x75339023, 0x1A225720,
    0x6CD1B38B, 0x7FFFFFFF, 0x65E759EB, 0x4EC9AC88,
    0x1F3F7FA1, 0x729BE305, 0x3DC609B0, 0x7E7F6F9F,
    0x5E24CAD8, 0x54769310, 0x229F842D, 0x20B95BE4,
    0x2504EA69, 0x516FEAD8, 0x1A86722E, 0x4DC19D74,
    0x4DBE1E23, 0x3AE3CEAC, 0x1FA3DB19, 0x5A45F8F3,
    0x7C95A780, 0x71BB8C5A, 0x32ADE534, 0x18E6298C,
    0x3739D80B, 0x52C6C5D3, 0x13E7290B, 0x0D292F6A,
    0x433B899D, 0x346B96C2, 0x0FD32AD6, 0x3E878F3C,
    0x43D2979F, 0x0F6B2936, 0x460E9B3F, 0x4377DEF8,
    0x3E6432AC, 0x26C80639, 0x551FC4C0, 0x69C6ADD3,
    0x402CFE4F, 0x2D94892B, 0x4D6CBA22, 0x22BFC198,
    0x2314B866, 0x1B78C4BA, 0x296F5825, 0x6A3DC342,
    0x73693C7B, 0x4F2F6196, 0x7F86CF86, 0x2B07AB00,
    0x4BC9BC21, 0x1CA9868C, 0x51E0F5B5, 0x0695FCF5,
    0x251684EB, 0x2B3EFA22, 0x6F4E429A, 0x4DF14171,
    0x0B99BCB0, 0x32D7367E, 0x1C634B7C, 0x314C46C0,
    0x3D8E5F6D, 0x03C3A3C5, 0x45E4ADF3, 0x44CBA613,
    0x2058B4D2, 0x0EF9554E, 0x58FC16D3, 0x431B5447,
    0x78085D5E, 0x3E0E9609, 0x79BFFDB0, 0x42020CF1,
    0x44AF640D, 0x6540E908, 0x25DF4B21, 0x1A7E760A,
    0x049A9900, 0x68DEF0C3, 0x2747866D, 0x62FC939E,
    0x6FCD3067, 0x2D025BD8, 0x5E81B8DD, 0x45807E62,
    0x17EB36D5, 0x4FF744BE, 0x0CB49561, 0x516971FB
    };

static const q7_t ref_q7[256] = {
    0x51, 0x62, 0x34, 0x5E, 0x02, 0x21, 0x02, 0x7F,
    0x38, 0x3F, 0x11, 0x61, 0x48, 0x43, 0x37, 0x67,
    0x6E, 0x67, 0x39, 0x0E, 0x43, 0x33, 0x3A, 0x06,
    0x6E, 0x1F, 0x7C, 0x4A, 0x45, 0x50, 0x03, 0x7B,
    0x51, 0x0C, 0x07, 0x5A, 0x19, 0x13, 0x10, 0x58,
    0x51, 0x09, 0x24, 0x78, 0x44, 0x01, 0x60, 0x6D,
    0x6E, 0x6B, 0x64, 0x38, 0x33, 0x30, 0x16, 0x66,
    0x4A, 0x2D, 0x4D, 0x12, 0x5C, 0x5B, 0x51, 0x3B,
    0x5B, 0x19, 0x13, 0x4D, 0x14, 0x2B, 0x44, 0x2C,
    0x72, 0x6C, 0x07, 0x34, 0x6A, 0x2C, 0x3A, 0x5C,
    0x5F, 0x32, 0x50, 0x7A, 0x5D, 0x1B, 0x47, 0x29,
    0x1F, 0x37, 0x0E, 0x4B, 0x3D, 0x4A, 0x23, 0x11,
    0x1D, 0x0D, 0x05, 0x3B, 0x32, 0x1C, 0x2D, 0x27,
    0x62, 0x68, 0x58, 0x6D, 0x2F, 0x44, 0x09, 0x6B,
    0x5D, 0x15, 0x01, 0x19, 0x52, 0x64, 0x7F, 0x33,
    0x38, 0x0C, 0x41, 0x3E, 0x3E, 0x33, 0x71, 0x25,
    0x2D, 0x10, 0x0D, 0x40, 0x4F, 0x5A, 0x13, 0x0C,
    0x6C, 0x7D, 0x72, 0x12, 0x5E, 0x07, 0x0D, 0x7C,
    0x5C, 0x4D, 0x2A, 0x3D, 0x74, 0x43, 0x00, 0x4D,
    0x34, 0x6E, 0x0A, 0x0E, 0x1C, 0x42, 0x5C, 0x08,
    0x4C, 0x56, 0x75, 0x1A, 0x6D, 0x7F, 0x66, 0x4F,
    0x1F, 0x73, 0x3E, 0x7E, 0x5E, 0x54, 0x23, 0x21,
    0x25, 0x51, 0x1B, 0x4E, 0x4E, 0x3B, 0x20, 0x5A,
    0x7D, 0x72, 0x33, 0x19, 0x37, 0x53, 0x14, 0x0D,
    0x43, 0x34, 0x10, 0x3F, 0x44, 0x0F, 0x46, 0x43,
    0x3E, 0x27, 0x55, 0x6A, 0x40, 0x2E, 0x4D, 0x23,
    0x23, 0x1B, 0x29, 0x6A, 0x73, 0x4F, 0x7F, 0x2B,
    0x4C, 0x1D, 0x52, 0x07, 0x25, 0x2B, 0x6F, 0x4E,
    0x0C, 0x33, 0x1C, 0x31, 0x3E, 0x04, 0x46, 0x45,
    0x20, 0x0F, 0x59, 0x43, 0x78, 0x3E, 0x7A, 0x42,
    0x45, 0x65, 0x26, 0x1A, 0x05, 0x69, 0x27, 0x63,
    0x70, 0x2D, 0x5F, 0x46, 0x18, 0x50, 0x0D, 0x51
    };

