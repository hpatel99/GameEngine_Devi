#include "Sphere.h"
Tri_index trilist[200];
Vert_xyzuvn VertData[121];

SphereModel::SphereModel(const char * const pModelFileName)
	:Model(Model::Name::SPHERE)
{
	assert(pModelFileName);
	this->privCreateVAO(pModelFileName);
}

SphereModel::~SphereModel()
{
}

void SphereModel::privCreateVAO(const char * const modelfileNAME)
{
	assert(modelfileNAME!= NULL);

	this->numtris = 200;
	this->numVerts = 121;
	Vert_xyzuvn pVerts[121];
	Tri_index triList[200];
	triList[0].v0 = 0;
	triList[0].v1 = 1;
	triList[0].v2 = 2;

	triList[1].v0 = 1;
	triList[1].v1 = 3;
	triList[1].v2 = 2;

	triList[2].v0 = 2;
	triList[2].v1 = 3;
	triList[2].v2 = 4;

	triList[3].v0 = 3;
	triList[3].v1 = 5;
	triList[3].v2 = 4;

	triList[4].v0 = 4;
	triList[4].v1 = 5;
	triList[4].v2 = 6;

	triList[5].v0 = 5;
	triList[5].v1 = 7;
	triList[5].v2 = 6;

	triList[6].v0 = 6;
	triList[6].v1 = 7;
	triList[6].v2 = 8;

	triList[7].v0 = 7;
	triList[7].v1 = 9;
	triList[7].v2 = 8;

	triList[8].v0 = 8;
	triList[8].v1 = 9;
	triList[8].v2 = 10;

	triList[9].v0 = 9;
	triList[9].v1 = 11;
	triList[9].v2 = 10;

	triList[10].v0 = 10;
	triList[10].v1 = 11;
	triList[10].v2 = 12;

	triList[11].v0 = 11;
	triList[11].v1 = 13;
	triList[11].v2 = 12;

	triList[12].v0 = 12;
	triList[12].v1 = 13;
	triList[12].v2 = 14;

	triList[13].v0 = 13;
	triList[13].v1 = 15;
	triList[13].v2 = 14;

	triList[14].v0 = 14;
	triList[14].v1 = 15;
	triList[14].v2 = 16;

	triList[15].v0 = 15;
	triList[15].v1 = 17;
	triList[15].v2 = 16;

	triList[16].v0 = 16;
	triList[16].v1 = 17;
	triList[16].v2 = 18;

	triList[17].v0 = 17;
	triList[17].v1 = 19;
	triList[17].v2 = 18;

	triList[18].v0 = 18;
	triList[18].v1 = 19;
	triList[18].v2 = 20;

	triList[19].v0 = 19;
	triList[19].v1 = 21;
	triList[19].v2 = 20;

	triList[20].v0 = 1;
	triList[20].v1 = 22;
	triList[20].v2 = 3;

	triList[21].v0 = 22;
	triList[21].v1 = 23;
	triList[21].v2 = 3;

	triList[22].v0 = 3;
	triList[22].v1 = 23;
	triList[22].v2 = 5;

	triList[23].v0 = 23;
	triList[23].v1 = 24;
	triList[23].v2 = 5;

	triList[24].v0 = 5;
	triList[24].v1 = 24;
	triList[24].v2 = 7;

	triList[25].v0 = 24;
	triList[25].v1 = 25;
	triList[25].v2 = 7;

	triList[26].v0 = 7;
	triList[26].v1 = 25;
	triList[26].v2 = 9;

	triList[27].v0 = 25;
	triList[27].v1 = 26;
	triList[27].v2 = 9;

	triList[28].v0 = 9;
	triList[28].v1 = 26;
	triList[28].v2 = 11;

	triList[29].v0 = 26;
	triList[29].v1 = 27;
	triList[29].v2 = 11;

	triList[30].v0 = 11;
	triList[30].v1 = 27;
	triList[30].v2 = 13;

	triList[31].v0 = 27;
	triList[31].v1 = 28;
	triList[31].v2 = 13;

	triList[32].v0 = 13;
	triList[32].v1 = 28;
	triList[32].v2 = 15;

	triList[33].v0 = 28;
	triList[33].v1 = 29;
	triList[33].v2 = 15;

	triList[34].v0 = 15;
	triList[34].v1 = 29;
	triList[34].v2 = 17;

	triList[35].v0 = 29;
	triList[35].v1 = 30;
	triList[35].v2 = 17;

	triList[36].v0 = 17;
	triList[36].v1 = 30;
	triList[36].v2 = 19;

	triList[37].v0 = 30;
	triList[37].v1 = 31;
	triList[37].v2 = 19;

	triList[38].v0 = 19;
	triList[38].v1 = 31;
	triList[38].v2 = 21;

	triList[39].v0 = 31;
	triList[39].v1 = 32;
	triList[39].v2 = 21;

	triList[40].v0 = 22;
	triList[40].v1 = 33;
	triList[40].v2 = 23;

	triList[41].v0 = 33;
	triList[41].v1 = 34;
	triList[41].v2 = 23;

	triList[42].v0 = 23;
	triList[42].v1 = 34;
	triList[42].v2 = 24;

	triList[43].v0 = 34;
	triList[43].v1 = 35;
	triList[43].v2 = 24;

	triList[44].v0 = 24;
	triList[44].v1 = 35;
	triList[44].v2 = 25;

	triList[45].v0 = 35;
	triList[45].v1 = 36;
	triList[45].v2 = 25;

	triList[46].v0 = 25;
	triList[46].v1 = 36;
	triList[46].v2 = 26;

	triList[47].v0 = 36;
	triList[47].v1 = 37;
	triList[47].v2 = 26;

	triList[48].v0 = 26;
	triList[48].v1 = 37;
	triList[48].v2 = 27;

	triList[49].v0 = 37;
	triList[49].v1 = 38;
	triList[49].v2 = 27;

	triList[50].v0 = 27;
	triList[50].v1 = 38;
	triList[50].v2 = 28;

	triList[51].v0 = 38;
	triList[51].v1 = 39;
	triList[51].v2 = 28;

	triList[52].v0 = 28;
	triList[52].v1 = 39;
	triList[52].v2 = 29;

	triList[53].v0 = 39;
	triList[53].v1 = 40;
	triList[53].v2 = 29;

	triList[54].v0 = 29;
	triList[54].v1 = 40;
	triList[54].v2 = 30;

	triList[55].v0 = 40;
	triList[55].v1 = 41;
	triList[55].v2 = 30;

	triList[56].v0 = 30;
	triList[56].v1 = 41;
	triList[56].v2 = 31;

	triList[57].v0 = 41;
	triList[57].v1 = 42;
	triList[57].v2 = 31;

	triList[58].v0 = 31;
	triList[58].v1 = 42;
	triList[58].v2 = 32;

	triList[59].v0 = 42;
	triList[59].v1 = 43;
	triList[59].v2 = 32;

	triList[60].v0 = 33;
	triList[60].v1 = 44;
	triList[60].v2 = 34;

	triList[61].v0 = 44;
	triList[61].v1 = 45;
	triList[61].v2 = 34;

	triList[62].v0 = 34;
	triList[62].v1 = 45;
	triList[62].v2 = 35;

	triList[63].v0 = 45;
	triList[63].v1 = 46;
	triList[63].v2 = 35;

	triList[64].v0 = 35;
	triList[64].v1 = 46;
	triList[64].v2 = 36;

	triList[65].v0 = 46;
	triList[65].v1 = 47;
	triList[65].v2 = 36;

	triList[66].v0 = 36;
	triList[66].v1 = 47;
	triList[66].v2 = 37;

	triList[67].v0 = 47;
	triList[67].v1 = 48;
	triList[67].v2 = 37;

	triList[68].v0 = 37;
	triList[68].v1 = 48;
	triList[68].v2 = 38;

	triList[69].v0 = 48;
	triList[69].v1 = 49;
	triList[69].v2 = 38;

	triList[70].v0 = 38;
	triList[70].v1 = 49;
	triList[70].v2 = 39;

	triList[71].v0 = 49;
	triList[71].v1 = 50;
	triList[71].v2 = 39;

	triList[72].v0 = 39;
	triList[72].v1 = 50;
	triList[72].v2 = 40;

	triList[73].v0 = 50;
	triList[73].v1 = 51;
	triList[73].v2 = 40;

	triList[74].v0 = 40;
	triList[74].v1 = 51;
	triList[74].v2 = 41;

	triList[75].v0 = 51;
	triList[75].v1 = 52;
	triList[75].v2 = 41;

	triList[76].v0 = 41;
	triList[76].v1 = 52;
	triList[76].v2 = 42;

	triList[77].v0 = 52;
	triList[77].v1 = 53;
	triList[77].v2 = 42;

	triList[78].v0 = 42;
	triList[78].v1 = 53;
	triList[78].v2 = 43;

	triList[79].v0 = 53;
	triList[79].v1 = 54;
	triList[79].v2 = 43;

	triList[80].v0 = 44;
	triList[80].v1 = 55;
	triList[80].v2 = 45;

	triList[81].v0 = 55;
	triList[81].v1 = 56;
	triList[81].v2 = 45;

	triList[82].v0 = 45;
	triList[82].v1 = 56;
	triList[82].v2 = 46;

	triList[83].v0 = 56;
	triList[83].v1 = 57;
	triList[83].v2 = 46;

	triList[84].v0 = 46;
	triList[84].v1 = 57;
	triList[84].v2 = 47;

	triList[85].v0 = 57;
	triList[85].v1 = 58;
	triList[85].v2 = 47;

	triList[86].v0 = 47;
	triList[86].v1 = 58;
	triList[86].v2 = 48;

	triList[87].v0 = 58;
	triList[87].v1 = 59;
	triList[87].v2 = 48;

	triList[88].v0 = 48;
	triList[88].v1 = 59;
	triList[88].v2 = 49;

	triList[89].v0 = 59;
	triList[89].v1 = 60;
	triList[89].v2 = 49;

	triList[90].v0 = 49;
	triList[90].v1 = 60;
	triList[90].v2 = 50;

	triList[91].v0 = 60;
	triList[91].v1 = 61;
	triList[91].v2 = 50;

	triList[92].v0 = 50;
	triList[92].v1 = 61;
	triList[92].v2 = 51;

	triList[93].v0 = 61;
	triList[93].v1 = 62;
	triList[93].v2 = 51;

	triList[94].v0 = 51;
	triList[94].v1 = 62;
	triList[94].v2 = 52;

	triList[95].v0 = 62;
	triList[95].v1 = 63;
	triList[95].v2 = 52;

	triList[96].v0 = 52;
	triList[96].v1 = 63;
	triList[96].v2 = 53;

	triList[97].v0 = 63;
	triList[97].v1 = 64;
	triList[97].v2 = 53;

	triList[98].v0 = 53;
	triList[98].v1 = 64;
	triList[98].v2 = 54;

	triList[99].v0 = 64;
	triList[99].v1 = 65;
	triList[99].v2 = 54;

	triList[100].v0 = 55;
	triList[100].v1 = 66;
	triList[100].v2 = 56;

	triList[101].v0 = 66;
	triList[101].v1 = 67;
	triList[101].v2 = 56;

	triList[102].v0 = 56;
	triList[102].v1 = 67;
	triList[102].v2 = 57;

	triList[103].v0 = 67;
	triList[103].v1 = 68;
	triList[103].v2 = 57;

	triList[104].v0 = 57;
	triList[104].v1 = 68;
	triList[104].v2 = 58;

	triList[105].v0 = 68;
	triList[105].v1 = 69;
	triList[105].v2 = 58;

	triList[106].v0 = 58;
	triList[106].v1 = 69;
	triList[106].v2 = 59;

	triList[107].v0 = 69;
	triList[107].v1 = 70;
	triList[107].v2 = 59;

	triList[108].v0 = 59;
	triList[108].v1 = 70;
	triList[108].v2 = 60;

	triList[109].v0 = 70;
	triList[109].v1 = 71;
	triList[109].v2 = 60;

	triList[110].v0 = 60;
	triList[110].v1 = 71;
	triList[110].v2 = 61;

	triList[111].v0 = 71;
	triList[111].v1 = 72;
	triList[111].v2 = 61;

	triList[112].v0 = 61;
	triList[112].v1 = 72;
	triList[112].v2 = 62;

	triList[113].v0 = 72;
	triList[113].v1 = 73;
	triList[113].v2 = 62;

	triList[114].v0 = 62;
	triList[114].v1 = 73;
	triList[114].v2 = 63;

	triList[115].v0 = 73;
	triList[115].v1 = 74;
	triList[115].v2 = 63;

	triList[116].v0 = 63;
	triList[116].v1 = 74;
	triList[116].v2 = 64;

	triList[117].v0 = 74;
	triList[117].v1 = 75;
	triList[117].v2 = 64;

	triList[118].v0 = 64;
	triList[118].v1 = 75;
	triList[118].v2 = 65;

	triList[119].v0 = 75;
	triList[119].v1 = 76;
	triList[119].v2 = 65;

	triList[120].v0 = 66;
	triList[120].v1 = 77;
	triList[120].v2 = 67;

	triList[121].v0 = 77;
	triList[121].v1 = 78;
	triList[121].v2 = 67;

	triList[122].v0 = 67;
	triList[122].v1 = 78;
	triList[122].v2 = 68;

	triList[123].v0 = 78;
	triList[123].v1 = 79;
	triList[123].v2 = 68;

	triList[124].v0 = 68;
	triList[124].v1 = 79;
	triList[124].v2 = 69;

	triList[125].v0 = 79;
	triList[125].v1 = 80;
	triList[125].v2 = 69;

	triList[126].v0 = 69;
	triList[126].v1 = 80;
	triList[126].v2 = 70;

	triList[127].v0 = 80;
	triList[127].v1 = 81;
	triList[127].v2 = 70;

	triList[128].v0 = 70;
	triList[128].v1 = 81;
	triList[128].v2 = 71;

	triList[129].v0 = 81;
	triList[129].v1 = 82;
	triList[129].v2 = 71;

	triList[130].v0 = 71;
	triList[130].v1 = 82;
	triList[130].v2 = 72;

	triList[131].v0 = 82;
	triList[131].v1 = 83;
	triList[131].v2 = 72;

	triList[132].v0 = 72;
	triList[132].v1 = 83;
	triList[132].v2 = 73;

	triList[133].v0 = 83;
	triList[133].v1 = 84;
	triList[133].v2 = 73;

	triList[134].v0 = 73;
	triList[134].v1 = 84;
	triList[134].v2 = 74;

	triList[135].v0 = 84;
	triList[135].v1 = 85;
	triList[135].v2 = 74;

	triList[136].v0 = 74;
	triList[136].v1 = 85;
	triList[136].v2 = 75;

	triList[137].v0 = 85;
	triList[137].v1 = 86;
	triList[137].v2 = 75;

	triList[138].v0 = 75;
	triList[138].v1 = 86;
	triList[138].v2 = 76;

	triList[139].v0 = 86;
	triList[139].v1 = 87;
	triList[139].v2 = 76;

	triList[140].v0 = 77;
	triList[140].v1 = 88;
	triList[140].v2 = 78;

	triList[141].v0 = 88;
	triList[141].v1 = 89;
	triList[141].v2 = 78;

	triList[142].v0 = 78;
	triList[142].v1 = 89;
	triList[142].v2 = 79;

	triList[143].v0 = 89;
	triList[143].v1 = 90;
	triList[143].v2 = 79;

	triList[144].v0 = 79;
	triList[144].v1 = 90;
	triList[144].v2 = 80;

	triList[145].v0 = 90;
	triList[145].v1 = 91;
	triList[145].v2 = 80;

	triList[146].v0 = 80;
	triList[146].v1 = 91;
	triList[146].v2 = 81;

	triList[147].v0 = 91;
	triList[147].v1 = 92;
	triList[147].v2 = 81;

	triList[148].v0 = 81;
	triList[148].v1 = 92;
	triList[148].v2 = 82;

	triList[149].v0 = 92;
	triList[149].v1 = 93;
	triList[149].v2 = 82;

	triList[150].v0 = 82;
	triList[150].v1 = 93;
	triList[150].v2 = 83;

	triList[151].v0 = 93;
	triList[151].v1 = 94;
	triList[151].v2 = 83;

	triList[152].v0 = 83;
	triList[152].v1 = 94;
	triList[152].v2 = 84;

	triList[153].v0 = 94;
	triList[153].v1 = 95;
	triList[153].v2 = 84;

	triList[154].v0 = 84;
	triList[154].v1 = 95;
	triList[154].v2 = 85;

	triList[155].v0 = 95;
	triList[155].v1 = 96;
	triList[155].v2 = 85;

	triList[156].v0 = 85;
	triList[156].v1 = 96;
	triList[156].v2 = 86;

	triList[157].v0 = 96;
	triList[157].v1 = 97;
	triList[157].v2 = 86;

	triList[158].v0 = 86;
	triList[158].v1 = 97;
	triList[158].v2 = 87;

	triList[159].v0 = 97;
	triList[159].v1 = 98;
	triList[159].v2 = 87;

	triList[160].v0 = 88;
	triList[160].v1 = 99;
	triList[160].v2 = 89;

	triList[161].v0 = 99;
	triList[161].v1 = 100;
	triList[161].v2 = 89;

	triList[162].v0 = 89;
	triList[162].v1 = 100;
	triList[162].v2 = 90;

	triList[163].v0 = 100;
	triList[163].v1 = 101;
	triList[163].v2 = 90;

	triList[164].v0 = 90;
	triList[164].v1 = 101;
	triList[164].v2 = 91;

	triList[165].v0 = 101;
	triList[165].v1 = 102;
	triList[165].v2 = 91;

	triList[166].v0 = 91;
	triList[166].v1 = 102;
	triList[166].v2 = 92;

	triList[167].v0 = 102;
	triList[167].v1 = 103;
	triList[167].v2 = 92;

	triList[168].v0 = 92;
	triList[168].v1 = 103;
	triList[168].v2 = 93;

	triList[169].v0 = 103;
	triList[169].v1 = 104;
	triList[169].v2 = 93;

	triList[170].v0 = 93;
	triList[170].v1 = 104;
	triList[170].v2 = 94;

	triList[171].v0 = 104;
	triList[171].v1 = 105;
	triList[171].v2 = 94;

	triList[172].v0 = 94;
	triList[172].v1 = 105;
	triList[172].v2 = 95;

	triList[173].v0 = 105;
	triList[173].v1 = 106;
	triList[173].v2 = 95;

	triList[174].v0 = 95;
	triList[174].v1 = 106;
	triList[174].v2 = 96;

	triList[175].v0 = 106;
	triList[175].v1 = 107;
	triList[175].v2 = 96;

	triList[176].v0 = 96;
	triList[176].v1 = 107;
	triList[176].v2 = 97;

	triList[177].v0 = 107;
	triList[177].v1 = 108;
	triList[177].v2 = 97;

	triList[178].v0 = 97;
	triList[178].v1 = 108;
	triList[178].v2 = 98;

	triList[179].v0 = 108;
	triList[179].v1 = 109;
	triList[179].v2 = 98;

	triList[180].v0 = 99;
	triList[180].v1 = 110;
	triList[180].v2 = 100;

	triList[181].v0 = 110;
	triList[181].v1 = 111;
	triList[181].v2 = 100;

	triList[182].v0 = 100;
	triList[182].v1 = 111;
	triList[182].v2 = 101;

	triList[183].v0 = 111;
	triList[183].v1 = 112;
	triList[183].v2 = 101;

	triList[184].v0 = 101;
	triList[184].v1 = 112;
	triList[184].v2 = 102;

	triList[185].v0 = 112;
	triList[185].v1 = 113;
	triList[185].v2 = 102;

	triList[186].v0 = 102;
	triList[186].v1 = 113;
	triList[186].v2 = 103;

	triList[187].v0 = 113;
	triList[187].v1 = 114;
	triList[187].v2 = 103;

	triList[188].v0 = 103;
	triList[188].v1 = 114;
	triList[188].v2 = 104;

	triList[189].v0 = 114;
	triList[189].v1 = 115;
	triList[189].v2 = 104;

	triList[190].v0 = 104;
	triList[190].v1 = 115;
	triList[190].v2 = 105;

	triList[191].v0 = 115;
	triList[191].v1 = 116;
	triList[191].v2 = 105;

	triList[192].v0 = 105;
	triList[192].v1 = 116;
	triList[192].v2 = 106;

	triList[193].v0 = 116;
	triList[193].v1 = 117;
	triList[193].v2 = 106;

	triList[194].v0 = 106;
	triList[194].v1 = 117;
	triList[194].v2 = 107;

	triList[195].v0 = 117;
	triList[195].v1 = 118;
	triList[195].v2 = 107;

	triList[196].v0 = 107;
	triList[196].v1 = 118;
	triList[196].v2 = 108;

	triList[197].v0 = 118;
	triList[197].v1 = 119;
	triList[197].v2 = 108;

	triList[198].v0 = 108;
	triList[198].v1 = 119;
	triList[198].v2 = 109;

	triList[199].v0 = 119;
	triList[199].v1 = 120;
	triList[199].v2 = 109;

	pVerts[0].x = -0.000000f;
	pVerts[0].y = 0.000000f;
	pVerts[0].z = 0.500000f;
	pVerts[0].nx = -0.000000f;
	pVerts[0].ny = 0.000000f;
	pVerts[0].nz = 1.000000f;
	pVerts[0].u = 0.000000f;
	pVerts[0].v = 1.000000f;

	pVerts[1].x = -0.000000f;
	pVerts[1].y = 0.154509f;
	pVerts[1].z = 0.475528f;
	pVerts[1].nx = -0.000000f;
	pVerts[1].ny = 0.309017f;
	pVerts[1].nz = 0.951057f;
	pVerts[1].u = 0.000000f;
	pVerts[1].v = 0.900000f;

	pVerts[2].x = -0.000000f;
	pVerts[2].y = 0.000000f;
	pVerts[2].z = 0.500000f;
	pVerts[2].nx = -0.000000f;
	pVerts[2].ny = 0.000000f;
	pVerts[2].nz = 1.000000f;
	pVerts[2].u = 0.100000f;
	pVerts[2].v = 1.000000f;

	pVerts[3].x = -0.090818f;
	pVerts[3].y = 0.125000f;
	pVerts[3].z = 0.475528f;
	pVerts[3].nx = -0.181636f;
	pVerts[3].ny = 0.250000f;
	pVerts[3].nz = 0.951057f;
	pVerts[3].u = 0.100000f;
	pVerts[3].v = 0.900000f;

	pVerts[4].x = -0.000000f;
	pVerts[4].y = 0.000000f;
	pVerts[4].z = 0.500000f;
	pVerts[4].nx = -0.000000f;
	pVerts[4].ny = 0.000000f;
	pVerts[4].nz = 1.000000f;
	pVerts[4].u = 0.200000f;
	pVerts[4].v = 1.000000f;

	pVerts[5].x = -0.146946f;
	pVerts[5].y = 0.047746f;
	pVerts[5].z = 0.475528f;
	pVerts[5].nx = -0.293893f;
	pVerts[5].ny = 0.095491f;
	pVerts[5].nz = 0.951057f;
	pVerts[5].u = 0.200000f;
	pVerts[5].v = 0.900000f;

	pVerts[6].x = -0.000000f;
	pVerts[6].y = -0.000000f;
	pVerts[6].z = 0.500000f;
	pVerts[6].nx = -0.000000f;
	pVerts[6].ny = -0.000000f;
	pVerts[6].nz = 1.000000f;
	pVerts[6].u = 0.300000f;
	pVerts[6].v = 1.000000f;

	pVerts[7].x = -0.146946f;
	pVerts[7].y = -0.047746f;
	pVerts[7].z = 0.475528f;
	pVerts[7].nx = -0.293893f;
	pVerts[7].ny = -0.095492f;
	pVerts[7].nz = 0.951057f;
	pVerts[7].u = 0.300000f;
	pVerts[7].v = 0.900000f;

	pVerts[8].x = -0.000000f;
	pVerts[8].y = -0.000000f;
	pVerts[8].z = 0.500000f;
	pVerts[8].nx = -0.000000f;
	pVerts[8].ny = -0.000000f;
	pVerts[8].nz = 1.000000f;
	pVerts[8].u = 0.400000f;
	pVerts[8].v = 1.000000f;

	pVerts[9].x = -0.090818f;
	pVerts[9].y = -0.125000f;
	pVerts[9].z = 0.475528f;
	pVerts[9].nx = -0.181636f;
	pVerts[9].ny = -0.250000f;
	pVerts[9].nz = 0.951057f;
	pVerts[9].u = 0.400000f;
	pVerts[9].v = 0.900000f;

	pVerts[10].x = 0.000000f;
	pVerts[10].y = -0.000000f;
	pVerts[10].z = 0.500000f;
	pVerts[10].nx = 0.000000f;
	pVerts[10].ny = -0.000000f;
	pVerts[10].nz = 1.000000f;
	pVerts[10].u = 0.500000f;
	pVerts[10].v = 1.000000f;

	pVerts[11].x = 0.000000f;
	pVerts[11].y = -0.154509f;
	pVerts[11].z = 0.475528f;
	pVerts[11].nx = 0.000000f;
	pVerts[11].ny = -0.309017f;
	pVerts[11].nz = 0.951057f;
	pVerts[11].u = 0.500000f;
	pVerts[11].v = 0.900000f;

	pVerts[12].x = 0.000000f;
	pVerts[12].y = -0.000000f;
	pVerts[12].z = 0.500000f;
	pVerts[12].nx = 0.000000f;
	pVerts[12].ny = -0.000000f;
	pVerts[12].nz = 1.000000f;
	pVerts[12].u = 0.600000f;
	pVerts[12].v = 1.000000f;

	pVerts[13].x = 0.090818f;
	pVerts[13].y = -0.125000f;
	pVerts[13].z = 0.475528f;
	pVerts[13].nx = 0.181636f;
	pVerts[13].ny = -0.250000f;
	pVerts[13].nz = 0.951057f;
	pVerts[13].u = 0.600000f;
	pVerts[13].v = 0.900000f;

	pVerts[14].x = 0.000000f;
	pVerts[14].y = -0.000000f;
	pVerts[14].z = 0.500000f;
	pVerts[14].nx = 0.000000f;
	pVerts[14].ny = -0.000000f;
	pVerts[14].nz = 1.000000f;
	pVerts[14].u = 0.700000f;
	pVerts[14].v = 1.000000f;

	pVerts[15].x = 0.146946f;
	pVerts[15].y = -0.047746f;
	pVerts[15].z = 0.475528f;
	pVerts[15].nx = 0.293893f;
	pVerts[15].ny = -0.095492f;
	pVerts[15].nz = 0.951057f;
	pVerts[15].u = 0.700000f;
	pVerts[15].v = 0.900000f;

	pVerts[16].x = 0.000000f;
	pVerts[16].y = 0.000000f;
	pVerts[16].z = 0.500000f;
	pVerts[16].nx = 0.000000f;
	pVerts[16].ny = 0.000000f;
	pVerts[16].nz = 1.000000f;
	pVerts[16].u = 0.800000f;
	pVerts[16].v = 1.000000f;

	pVerts[17].x = 0.146946f;
	pVerts[17].y = 0.047746f;
	pVerts[17].z = 0.475528f;
	pVerts[17].nx = 0.293893f;
	pVerts[17].ny = 0.095492f;
	pVerts[17].nz = 0.951057f;
	pVerts[17].u = 0.800000f;
	pVerts[17].v = 0.900000f;

	pVerts[18].x = 0.000000f;
	pVerts[18].y = 0.000000f;
	pVerts[18].z = 0.500000f;
	pVerts[18].nx = 0.000000f;
	pVerts[18].ny = 0.000000f;
	pVerts[18].nz = 1.000000f;
	pVerts[18].u = 0.900000f;
	pVerts[18].v = 1.000000f;

	pVerts[19].x = 0.090818f;
	pVerts[19].y = 0.125000f;
	pVerts[19].z = 0.475528f;
	pVerts[19].nx = 0.181636f;
	pVerts[19].ny = 0.250000f;
	pVerts[19].nz = 0.951057f;
	pVerts[19].u = 0.900000f;
	pVerts[19].v = 0.900000f;

	pVerts[20].x = -0.000000f;
	pVerts[20].y = 0.000000f;
	pVerts[20].z = 0.500000f;
	pVerts[20].nx = -0.000000f;
	pVerts[20].ny = 0.000000f;
	pVerts[20].nz = 1.000000f;
	pVerts[20].u = 1.000000f;
	pVerts[20].v = 1.000000f;

	pVerts[21].x = -0.000000f;
	pVerts[21].y = 0.154509f;
	pVerts[21].z = 0.475528f;
	pVerts[21].nx = -0.000000f;
	pVerts[21].ny = 0.309017f;
	pVerts[21].nz = 0.951057f;
	pVerts[21].u = 1.000000f;
	pVerts[21].v = 0.900000f;

	pVerts[22].x = -0.000000f;
	pVerts[22].y = 0.293893f;
	pVerts[22].z = 0.404509f;
	pVerts[22].nx = -0.000000f;
	pVerts[22].ny = 0.587785f;
	pVerts[22].nz = 0.809017f;
	pVerts[22].u = 0.000000f;
	pVerts[22].v = 0.800000f;

	pVerts[23].x = -0.172746f;
	pVerts[23].y = 0.237764f;
	pVerts[23].z = 0.404509f;
	pVerts[23].nx = -0.345491f;
	pVerts[23].ny = 0.475528f;
	pVerts[23].nz = 0.809017f;
	pVerts[23].u = 0.100000f;
	pVerts[23].v = 0.800000f;

	pVerts[24].x = -0.279509f;
	pVerts[24].y = 0.090818f;
	pVerts[24].z = 0.404509f;
	pVerts[24].nx = -0.559017f;
	pVerts[24].ny = 0.181636f;
	pVerts[24].nz = 0.809017f;
	pVerts[24].u = 0.200000f;
	pVerts[24].v = 0.800000f;

	pVerts[25].x = -0.279508f;
	pVerts[25].y = -0.090818f;
	pVerts[25].z = 0.404509f;
	pVerts[25].nx = -0.559017f;
	pVerts[25].ny = -0.181636f;
	pVerts[25].nz = 0.809017f;
	pVerts[25].u = 0.300000f;
	pVerts[25].v = 0.800000f;

	pVerts[26].x = -0.172746f;
	pVerts[26].y = -0.237764f;
	pVerts[26].z = 0.404509f;
	pVerts[26].nx = -0.345491f;
	pVerts[26].ny = -0.475528f;
	pVerts[26].nz = 0.809017f;
	pVerts[26].u = 0.400000f;
	pVerts[26].v = 0.800000f;

	pVerts[27].x = 0.000000f;
	pVerts[27].y = -0.293893f;
	pVerts[27].z = 0.404509f;
	pVerts[27].nx = 0.000000f;
	pVerts[27].ny = -0.587785f;
	pVerts[27].nz = 0.809017f;
	pVerts[27].u = 0.500000f;
	pVerts[27].v = 0.800000f;

	pVerts[28].x = 0.172746f;
	pVerts[28].y = -0.237764f;
	pVerts[28].z = 0.404509f;
	pVerts[28].nx = 0.345492f;
	pVerts[28].ny = -0.475528f;
	pVerts[28].nz = 0.809017f;
	pVerts[28].u = 0.600000f;
	pVerts[28].v = 0.800000f;

	pVerts[29].x = 0.279508f;
	pVerts[29].y = -0.090818f;
	pVerts[29].z = 0.404509f;
	pVerts[29].nx = 0.559017f;
	pVerts[29].ny = -0.181636f;
	pVerts[29].nz = 0.809017f;
	pVerts[29].u = 0.700000f;
	pVerts[29].v = 0.800000f;

	pVerts[30].x = 0.279508f;
	pVerts[30].y = 0.090818f;
	pVerts[30].z = 0.404509f;
	pVerts[30].nx = 0.559017f;
	pVerts[30].ny = 0.181636f;
	pVerts[30].nz = 0.809017f;
	pVerts[30].u = 0.800000f;
	pVerts[30].v = 0.800000f;

	pVerts[31].x = 0.172746f;
	pVerts[31].y = 0.237764f;
	pVerts[31].z = 0.404509f;
	pVerts[31].nx = 0.345491f;
	pVerts[31].ny = 0.475528f;
	pVerts[31].nz = 0.809017f;
	pVerts[31].u = 0.900000f;
	pVerts[31].v = 0.800000f;

	pVerts[32].x = -0.000000f;
	pVerts[32].y = 0.293893f;
	pVerts[32].z = 0.404509f;
	pVerts[32].nx = -0.000000f;
	pVerts[32].ny = 0.587785f;
	pVerts[32].nz = 0.809017f;
	pVerts[32].u = 1.000000f;
	pVerts[32].v = 0.800000f;

	pVerts[33].x = -0.000000f;
	pVerts[33].y = 0.404509f;
	pVerts[33].z = 0.293893f;
	pVerts[33].nx = -0.000000f;
	pVerts[33].ny = 0.809017f;
	pVerts[33].nz = 0.587785f;
	pVerts[33].u = 0.000000f;
	pVerts[33].v = 0.700000f;

	pVerts[34].x = -0.237764f;
	pVerts[34].y = 0.327254f;
	pVerts[34].z = 0.293893f;
	pVerts[34].nx = -0.475528f;
	pVerts[34].ny = 0.654509f;
	pVerts[34].nz = 0.587785f;
	pVerts[34].u = 0.100000f;
	pVerts[34].v = 0.700000f;

	pVerts[35].x = -0.384710f;
	pVerts[35].y = 0.125000f;
	pVerts[35].z = 0.293893f;
	pVerts[35].nx = -0.769421f;
	pVerts[35].ny = 0.250000f;
	pVerts[35].nz = 0.587785f;
	pVerts[35].u = 0.200000f;
	pVerts[35].v = 0.700000f;

	pVerts[36].x = -0.384710f;
	pVerts[36].y = -0.125000f;
	pVerts[36].z = 0.293893f;
	pVerts[36].nx = -0.769421f;
	pVerts[36].ny = -0.250000f;
	pVerts[36].nz = 0.587785f;
	pVerts[36].u = 0.300000f;
	pVerts[36].v = 0.700000f;

	pVerts[37].x = -0.237764f;
	pVerts[37].y = -0.327254f;
	pVerts[37].z = 0.293893f;
	pVerts[37].nx = -0.475528f;
	pVerts[37].ny = -0.654509f;
	pVerts[37].nz = 0.587785f;
	pVerts[37].u = 0.400000f;
	pVerts[37].v = 0.700000f;

	pVerts[38].x = 0.000000f;
	pVerts[38].y = -0.404509f;
	pVerts[38].z = 0.293893f;
	pVerts[38].nx = 0.000000f;
	pVerts[38].ny = -0.809017f;
	pVerts[38].nz = 0.587785f;
	pVerts[38].u = 0.500000f;
	pVerts[38].v = 0.700000f;

	pVerts[39].x = 0.237764f;
	pVerts[39].y = -0.327254f;
	pVerts[39].z = 0.293893f;
	pVerts[39].nx = 0.475528f;
	pVerts[39].ny = -0.654508f;
	pVerts[39].nz = 0.587785f;
	pVerts[39].u = 0.600000f;
	pVerts[39].v = 0.700000f;

	pVerts[40].x = 0.384710f;
	pVerts[40].y = -0.125000f;
	pVerts[40].z = 0.293893f;
	pVerts[40].nx = 0.769421f;
	pVerts[40].ny = -0.250000f;
	pVerts[40].nz = 0.587785f;
	pVerts[40].u = 0.700000f;
	pVerts[40].v = 0.700000f;

	pVerts[41].x = 0.384710f;
	pVerts[41].y = 0.125000f;
	pVerts[41].z = 0.293893f;
	pVerts[41].nx = 0.769421f;
	pVerts[41].ny = 0.250000f;
	pVerts[41].nz = 0.587785f;
	pVerts[41].u = 0.800000f;
	pVerts[41].v = 0.700000f;

	pVerts[42].x = 0.237764f;
	pVerts[42].y = 0.327254f;
	pVerts[42].z = 0.293893f;
	pVerts[42].nx = 0.475528f;
	pVerts[42].ny = 0.654509f;
	pVerts[42].nz = 0.587785f;
	pVerts[42].u = 0.900000f;
	pVerts[42].v = 0.700000f;

	pVerts[43].x = -0.000000f;
	pVerts[43].y = 0.404509f;
	pVerts[43].z = 0.293893f;
	pVerts[43].nx = -0.000000f;
	pVerts[43].ny = 0.809017f;
	pVerts[43].nz = 0.587785f;
	pVerts[43].u = 1.000000f;
	pVerts[43].v = 0.700000f;

	pVerts[44].x = -0.000000f;
	pVerts[44].y = 0.475528f;
	pVerts[44].z = 0.154508f;
	pVerts[44].nx = -0.000000f;
	pVerts[44].ny = 0.951057f;
	pVerts[44].nz = 0.309017f;
	pVerts[44].u = 0.000000f;
	pVerts[44].v = 0.600000f;

	pVerts[45].x = -0.279509f;
	pVerts[45].y = 0.384710f;
	pVerts[45].z = 0.154508f;
	pVerts[45].nx = -0.559017f;
	pVerts[45].ny = 0.769421f;
	pVerts[45].nz = 0.309017f;
	pVerts[45].u = 0.100000f;
	pVerts[45].v = 0.600000f;

	pVerts[46].x = -0.452254f;
	pVerts[46].y = 0.146946f;
	pVerts[46].z = 0.154508f;
	pVerts[46].nx = -0.904509f;
	pVerts[46].ny = 0.293893f;
	pVerts[46].nz = 0.309017f;
	pVerts[46].u = 0.200000f;
	pVerts[46].v = 0.600000f;

	pVerts[47].x = -0.452254f;
	pVerts[47].y = -0.146946f;
	pVerts[47].z = 0.154508f;
	pVerts[47].nx = -0.904508f;
	pVerts[47].ny = -0.293893f;
	pVerts[47].nz = 0.309017f;
	pVerts[47].u = 0.300000f;
	pVerts[47].v = 0.600000f;

	pVerts[48].x = -0.279508f;
	pVerts[48].y = -0.384710f;
	pVerts[48].z = 0.154508f;
	pVerts[48].nx = -0.559017f;
	pVerts[48].ny = -0.769421f;
	pVerts[48].nz = 0.309017f;
	pVerts[48].u = 0.400000f;
	pVerts[48].v = 0.600000f;

	pVerts[49].x = 0.000000f;
	pVerts[49].y = -0.475528f;
	pVerts[49].z = 0.154508f;
	pVerts[49].nx = 0.000000f;
	pVerts[49].ny = -0.951057f;
	pVerts[49].nz = 0.309017f;
	pVerts[49].u = 0.500000f;
	pVerts[49].v = 0.600000f;

	pVerts[50].x = 0.279509f;
	pVerts[50].y = -0.384710f;
	pVerts[50].z = 0.154508f;
	pVerts[50].nx = 0.559017f;
	pVerts[50].ny = -0.769421f;
	pVerts[50].nz = 0.309017f;
	pVerts[50].u = 0.600000f;
	pVerts[50].v = 0.600000f;

	pVerts[51].x = 0.452254f;
	pVerts[51].y = -0.146946f;
	pVerts[51].z = 0.154508f;
	pVerts[51].nx = 0.904508f;
	pVerts[51].ny = -0.293893f;
	pVerts[51].nz = 0.309017f;
	pVerts[51].u = 0.700000f;
	pVerts[51].v = 0.600000f;

	pVerts[52].x = 0.452254f;
	pVerts[52].y = 0.146946f;
	pVerts[52].z = 0.154508f;
	pVerts[52].nx = 0.904508f;
	pVerts[52].ny = 0.293893f;
	pVerts[52].nz = 0.309017f;
	pVerts[52].u = 0.800000f;
	pVerts[52].v = 0.600000f;

	pVerts[53].x = 0.279508f;
	pVerts[53].y = 0.384711f;
	pVerts[53].z = 0.154508f;
	pVerts[53].nx = 0.559017f;
	pVerts[53].ny = 0.769421f;
	pVerts[53].nz = 0.309017f;
	pVerts[53].u = 0.900000f;
	pVerts[53].v = 0.600000f;

	pVerts[54].x = -0.000000f;
	pVerts[54].y = 0.475528f;
	pVerts[54].z = 0.154508f;
	pVerts[54].nx = -0.000000f;
	pVerts[54].ny = 0.951057f;
	pVerts[54].nz = 0.309017f;
	pVerts[54].u = 1.000000f;
	pVerts[54].v = 0.600000f;

	pVerts[55].x = -0.000000f;
	pVerts[55].y = 0.500000f;
	pVerts[55].z = -0.000000f;
	pVerts[55].nx = -0.000000f;
	pVerts[55].ny = 1.000000f;
	pVerts[55].nz = -0.000000f;
	pVerts[55].u = 0.000000f;
	pVerts[55].v = 0.500000f;

	pVerts[56].x = -0.293893f;
	pVerts[56].y = 0.404509f;
	pVerts[56].z = -0.000000f;
	pVerts[56].nx = -0.587785f;
	pVerts[56].ny = 0.809017f;
	pVerts[56].nz = -0.000000f;
	pVerts[56].u = 0.100000f;
	pVerts[56].v = 0.500000f;

	pVerts[57].x = -0.475528f;
	pVerts[57].y = 0.154508f;
	pVerts[57].z = -0.000000f;
	pVerts[57].nx = -0.951057f;
	pVerts[57].ny = 0.309017f;
	pVerts[57].nz = -0.000000f;
	pVerts[57].u = 0.200000f;
	pVerts[57].v = 0.500000f;

	pVerts[58].x = -0.475528f;
	pVerts[58].y = -0.154509f;
	pVerts[58].z = -0.000000f;
	pVerts[58].nx = -0.951057f;
	pVerts[58].ny = -0.309017f;
	pVerts[58].nz = -0.000000f;
	pVerts[58].u = 0.300000f;
	pVerts[58].v = 0.500000f;

	pVerts[59].x = -0.293893f;
	pVerts[59].y = -0.404509f;
	pVerts[59].z = -0.000000f;
	pVerts[59].nx = -0.587785f;
	pVerts[59].ny = -0.809017f;
	pVerts[59].nz = -0.000000f;
	pVerts[59].u = 0.400000f;
	pVerts[59].v = 0.500000f;

	pVerts[60].x = 0.000000f;
	pVerts[60].y = -0.500000f;
	pVerts[60].z = -0.000000f;
	pVerts[60].nx = 0.000000f;
	pVerts[60].ny = -1.000000f;
	pVerts[60].nz = -0.000000f;
	pVerts[60].u = 0.500000f;
	pVerts[60].v = 0.500000f;

	pVerts[61].x = 0.293893f;
	pVerts[61].y = -0.404508f;
	pVerts[61].z = -0.000000f;
	pVerts[61].nx = 0.587785f;
	pVerts[61].ny = -0.809017f;
	pVerts[61].nz = -0.000000f;
	pVerts[61].u = 0.600000f;
	pVerts[61].v = 0.500000f;

	pVerts[62].x = 0.475528f;
	pVerts[62].y = -0.154509f;
	pVerts[62].z = -0.000000f;
	pVerts[62].nx = 0.951056f;
	pVerts[62].ny = -0.309017f;
	pVerts[62].nz = -0.000000f;
	pVerts[62].u = 0.700000f;
	pVerts[62].v = 0.500000f;

	pVerts[63].x = 0.475528f;
	pVerts[63].y = 0.154509f;
	pVerts[63].z = -0.000000f;
	pVerts[63].nx = 0.951056f;
	pVerts[63].ny = 0.309017f;
	pVerts[63].nz = -0.000000f;
	pVerts[63].u = 0.800000f;
	pVerts[63].v = 0.500000f;

	pVerts[64].x = 0.293892f;
	pVerts[64].y = 0.404509f;
	pVerts[64].z = -0.000000f;
	pVerts[64].nx = 0.587785f;
	pVerts[64].ny = 0.809017f;
	pVerts[64].nz = -0.000000f;
	pVerts[64].u = 0.900000f;
	pVerts[64].v = 0.500000f;

	pVerts[65].x = -0.000000f;
	pVerts[65].y = 0.500000f;
	pVerts[65].z = -0.000000f;
	pVerts[65].nx = -0.000000f;
	pVerts[65].ny = 1.000000f;
	pVerts[65].nz = -0.000000f;
	pVerts[65].u = 1.000000f;
	pVerts[65].v = 0.500000f;

	pVerts[66].x = -0.000000f;
	pVerts[66].y = 0.475528f;
	pVerts[66].z = -0.154509f;
	pVerts[66].nx = -0.000000f;
	pVerts[66].ny = 0.951057f;
	pVerts[66].nz = -0.309017f;
	pVerts[66].u = 0.000000f;
	pVerts[66].v = 0.400000f;

	pVerts[67].x = -0.279508f;
	pVerts[67].y = 0.384710f;
	pVerts[67].z = -0.154509f;
	pVerts[67].nx = -0.559017f;
	pVerts[67].ny = 0.769421f;
	pVerts[67].nz = -0.309017f;
	pVerts[67].u = 0.100000f;
	pVerts[67].v = 0.400000f;

	pVerts[68].x = -0.452254f;
	pVerts[68].y = 0.146946f;
	pVerts[68].z = -0.154509f;
	pVerts[68].nx = -0.904509f;
	pVerts[68].ny = 0.293893f;
	pVerts[68].nz = -0.309017f;
	pVerts[68].u = 0.200000f;
	pVerts[68].v = 0.400000f;

	pVerts[69].x = -0.452254f;
	pVerts[69].y = -0.146946f;
	pVerts[69].z = -0.154509f;
	pVerts[69].nx = -0.904509f;
	pVerts[69].ny = -0.293893f;
	pVerts[69].nz = -0.309017f;
	pVerts[69].u = 0.300000f;
	pVerts[69].v = 0.400000f;

	pVerts[70].x = -0.279508f;
	pVerts[70].y = -0.384710f;
	pVerts[70].z = -0.154509f;
	pVerts[70].nx = -0.559017f;
	pVerts[70].ny = -0.769421f;
	pVerts[70].nz = -0.309017f;
	pVerts[70].u = 0.400000f;
	pVerts[70].v = 0.400000f;

	pVerts[71].x = 0.000000f;
	pVerts[71].y = -0.475528f;
	pVerts[71].z = -0.154509f;
	pVerts[71].nx = 0.000000f;
	pVerts[71].ny = -0.951057f;
	pVerts[71].nz = -0.309017f;
	pVerts[71].u = 0.500000f;
	pVerts[71].v = 0.400000f;

	pVerts[72].x = 0.279509f;
	pVerts[72].y = -0.384710f;
	pVerts[72].z = -0.154509f;
	pVerts[72].nx = 0.559017f;
	pVerts[72].ny = -0.769421f;
	pVerts[72].nz = -0.309017f;
	pVerts[72].u = 0.600000f;
	pVerts[72].v = 0.400000f;

	pVerts[73].x = 0.452254f;
	pVerts[73].y = -0.146946f;
	pVerts[73].z = -0.154509f;
	pVerts[73].nx = 0.904509f;
	pVerts[73].ny = -0.293893f;
	pVerts[73].nz = -0.309017f;
	pVerts[73].u = 0.700000f;
	pVerts[73].v = 0.400000f;

	pVerts[74].x = 0.452254f;
	pVerts[74].y = 0.146946f;
	pVerts[74].z = -0.154509f;
	pVerts[74].nx = 0.904509f;
	pVerts[74].ny = 0.293893f;
	pVerts[74].nz = -0.309017f;
	pVerts[74].u = 0.800000f;
	pVerts[74].v = 0.400000f;

	pVerts[75].x = 0.279508f;
	pVerts[75].y = 0.384711f;
	pVerts[75].z = -0.154509f;
	pVerts[75].nx = 0.559017f;
	pVerts[75].ny = 0.769421f;
	pVerts[75].nz = -0.309017f;
	pVerts[75].u = 0.900000f;
	pVerts[75].v = 0.400000f;

	pVerts[76].x = -0.000000f;
	pVerts[76].y = 0.475528f;
	pVerts[76].z = -0.154509f;
	pVerts[76].nx = -0.000000f;
	pVerts[76].ny = 0.951057f;
	pVerts[76].nz = -0.309017f;
	pVerts[76].u = 1.000000f;
	pVerts[76].v = 0.400000f;

	pVerts[77].x = -0.000000f;
	pVerts[77].y = 0.404509f;
	pVerts[77].z = -0.293893f;
	pVerts[77].nx = -0.000000f;
	pVerts[77].ny = 0.809017f;
	pVerts[77].nz = -0.587785f;
	pVerts[77].u = 0.000000f;
	pVerts[77].v = 0.300000f;

	pVerts[78].x = -0.237764f;
	pVerts[78].y = 0.327254f;
	pVerts[78].z = -0.293893f;
	pVerts[78].nx = -0.475528f;
	pVerts[78].ny = 0.654509f;
	pVerts[78].nz = -0.587785f;
	pVerts[78].u = 0.100000f;
	pVerts[78].v = 0.300000f;

	pVerts[79].x = -0.384710f;
	pVerts[79].y = 0.125000f;
	pVerts[79].z = -0.293893f;
	pVerts[79].nx = -0.769421f;
	pVerts[79].ny = 0.250000f;
	pVerts[79].nz = -0.587785f;
	pVerts[79].u = 0.200000f;
	pVerts[79].v = 0.300000f;

	pVerts[80].x = -0.384710f;
	pVerts[80].y = -0.125000f;
	pVerts[80].z = -0.293893f;
	pVerts[80].nx = -0.769421f;
	pVerts[80].ny = -0.250000f;
	pVerts[80].nz = -0.587785f;
	pVerts[80].u = 0.300000f;
	pVerts[80].v = 0.300000f;

	pVerts[81].x = -0.237764f;
	pVerts[81].y = -0.327254f;
	pVerts[81].z = -0.293893f;
	pVerts[81].nx = -0.475528f;
	pVerts[81].ny = -0.654509f;
	pVerts[81].nz = -0.587785f;
	pVerts[81].u = 0.400000f;
	pVerts[81].v = 0.300000f;

	pVerts[82].x = 0.000000f;
	pVerts[82].y = -0.404509f;
	pVerts[82].z = -0.293893f;
	pVerts[82].nx = 0.000000f;
	pVerts[82].ny = -0.809017f;
	pVerts[82].nz = -0.587785f;
	pVerts[82].u = 0.500000f;
	pVerts[82].v = 0.300000f;

	pVerts[83].x = 0.237764f;
	pVerts[83].y = -0.327254f;
	pVerts[83].z = -0.293893f;
	pVerts[83].nx = 0.475528f;
	pVerts[83].ny = -0.654508f;
	pVerts[83].nz = -0.587785f;
	pVerts[83].u = 0.600000f;
	pVerts[83].v = 0.300000f;

	pVerts[84].x = 0.384710f;
	pVerts[84].y = -0.125000f;
	pVerts[84].z = -0.293893f;
	pVerts[84].nx = 0.769421f;
	pVerts[84].ny = -0.250000f;
	pVerts[84].nz = -0.587785f;
	pVerts[84].u = 0.700000f;
	pVerts[84].v = 0.300000f;

	pVerts[85].x = 0.384710f;
	pVerts[85].y = 0.125000f;
	pVerts[85].z = -0.293893f;
	pVerts[85].nx = 0.769421f;
	pVerts[85].ny = 0.250000f;
	pVerts[85].nz = -0.587785f;
	pVerts[85].u = 0.800000f;
	pVerts[85].v = 0.300000f;

	pVerts[86].x = 0.237764f;
	pVerts[86].y = 0.327254f;
	pVerts[86].z = -0.293893f;
	pVerts[86].nx = 0.475528f;
	pVerts[86].ny = 0.654509f;
	pVerts[86].nz = -0.587785f;
	pVerts[86].u = 0.900000f;
	pVerts[86].v = 0.300000f;

	pVerts[87].x = -0.000000f;
	pVerts[87].y = 0.404509f;
	pVerts[87].z = -0.293893f;
	pVerts[87].nx = -0.000000f;
	pVerts[87].ny = 0.809017f;
	pVerts[87].nz = -0.587785f;
	pVerts[87].u = 1.000000f;
	pVerts[87].v = 0.300000f;

	pVerts[88].x = -0.000000f;
	pVerts[88].y = 0.293893f;
	pVerts[88].z = -0.404509f;
	pVerts[88].nx = -0.000000f;
	pVerts[88].ny = 0.587785f;
	pVerts[88].nz = -0.809017f;
	pVerts[88].u = 0.000000f;
	pVerts[88].v = 0.200000f;

	pVerts[89].x = -0.172746f;
	pVerts[89].y = 0.237764f;
	pVerts[89].z = -0.404509f;
	pVerts[89].nx = -0.345491f;
	pVerts[89].ny = 0.475528f;
	pVerts[89].nz = -0.809017f;
	pVerts[89].u = 0.100000f;
	pVerts[89].v = 0.200000f;

	pVerts[90].x = -0.279508f;
	pVerts[90].y = 0.090818f;
	pVerts[90].z = -0.404509f;
	pVerts[90].nx = -0.559017f;
	pVerts[90].ny = 0.181636f;
	pVerts[90].nz = -0.809017f;
	pVerts[90].u = 0.200000f;
	pVerts[90].v = 0.200000f;

	pVerts[91].x = -0.279508f;
	pVerts[91].y = -0.090818f;
	pVerts[91].z = -0.404509f;
	pVerts[91].nx = -0.559017f;
	pVerts[91].ny = -0.181636f;
	pVerts[91].nz = -0.809017f;
	pVerts[91].u = 0.300000f;
	pVerts[91].v = 0.200000f;

	pVerts[92].x = -0.172746f;
	pVerts[92].y = -0.237764f;
	pVerts[92].z = -0.404509f;
	pVerts[92].nx = -0.345491f;
	pVerts[92].ny = -0.475528f;
	pVerts[92].nz = -0.809017f;
	pVerts[92].u = 0.400000f;
	pVerts[92].v = 0.200000f;

	pVerts[93].x = 0.000000f;
	pVerts[93].y = -0.293893f;
	pVerts[93].z = -0.404509f;
	pVerts[93].nx = 0.000000f;
	pVerts[93].ny = -0.587785f;
	pVerts[93].nz = -0.809017f;
	pVerts[93].u = 0.500000f;
	pVerts[93].v = 0.200000f;

	pVerts[94].x = 0.172746f;
	pVerts[94].y = -0.237764f;
	pVerts[94].z = -0.404509f;
	pVerts[94].nx = 0.345492f;
	pVerts[94].ny = -0.475528f;
	pVerts[94].nz = -0.809017f;
	pVerts[94].u = 0.600000f;
	pVerts[94].v = 0.200000f;

	pVerts[95].x = 0.279508f;
	pVerts[95].y = -0.090818f;
	pVerts[95].z = -0.404509f;
	pVerts[95].nx = 0.559017f;
	pVerts[95].ny = -0.181636f;
	pVerts[95].nz = -0.809017f;
	pVerts[95].u = 0.700000f;
	pVerts[95].v = 0.200000f;

	pVerts[96].x = 0.279508f;
	pVerts[96].y = 0.090818f;
	pVerts[96].z = -0.404509f;
	pVerts[96].nx = 0.559017f;
	pVerts[96].ny = 0.181636f;
	pVerts[96].nz = -0.809017f;
	pVerts[96].u = 0.800000f;
	pVerts[96].v = 0.200000f;

	pVerts[97].x = 0.172746f;
	pVerts[97].y = 0.237764f;
	pVerts[97].z = -0.404509f;
	pVerts[97].nx = 0.345491f;
	pVerts[97].ny = 0.475528f;
	pVerts[97].nz = -0.809017f;
	pVerts[97].u = 0.900000f;
	pVerts[97].v = 0.200000f;

	pVerts[98].x = -0.000000f;
	pVerts[98].y = 0.293893f;
	pVerts[98].z = -0.404509f;
	pVerts[98].nx = -0.000000f;
	pVerts[98].ny = 0.587785f;
	pVerts[98].nz = -0.809017f;
	pVerts[98].u = 1.000000f;
	pVerts[98].v = 0.200000f;

	pVerts[99].x = -0.000000f;
	pVerts[99].y = 0.154508f;
	pVerts[99].z = -0.475528f;
	pVerts[99].nx = -0.000000f;
	pVerts[99].ny = 0.309017f;
	pVerts[99].nz = -0.951057f;
	pVerts[99].u = 0.000000f;
	pVerts[99].v = 0.100000f;

	pVerts[100].x = -0.090818f;
	pVerts[100].y = 0.125000f;
	pVerts[100].z = -0.475528f;
	pVerts[100].nx = -0.181636f;
	pVerts[100].ny = 0.250000f;
	pVerts[100].nz = -0.951057f;
	pVerts[100].u = 0.100000f;
	pVerts[100].v = 0.100000f;

	pVerts[101].x = -0.146946f;
	pVerts[101].y = 0.047746f;
	pVerts[101].z = -0.475528f;
	pVerts[101].nx = -0.293892f;
	pVerts[101].ny = 0.095491f;
	pVerts[101].nz = -0.951057f;
	pVerts[101].u = 0.200000f;
	pVerts[101].v = 0.100000f;

	pVerts[102].x = -0.146946f;
	pVerts[102].y = -0.047746f;
	pVerts[102].z = -0.475528f;
	pVerts[102].nx = -0.293892f;
	pVerts[102].ny = -0.095491f;
	pVerts[102].nz = -0.951057f;
	pVerts[102].u = 0.300000f;
	pVerts[102].v = 0.100000f;

	pVerts[103].x = -0.090818f;
	pVerts[103].y = -0.125000f;
	pVerts[103].z = -0.475528f;
	pVerts[103].nx = -0.181635f;
	pVerts[103].ny = -0.250000f;
	pVerts[103].nz = -0.951057f;
	pVerts[103].u = 0.400000f;
	pVerts[103].v = 0.100000f;

	pVerts[104].x = 0.000000f;
	pVerts[104].y = -0.154508f;
	pVerts[104].z = -0.475528f;
	pVerts[104].nx = 0.000000f;
	pVerts[104].ny = -0.309017f;
	pVerts[104].nz = -0.951057f;
	pVerts[104].u = 0.500000f;
	pVerts[104].v = 0.100000f;

	pVerts[105].x = 0.090818f;
	pVerts[105].y = -0.125000f;
	pVerts[105].z = -0.475528f;
	pVerts[105].nx = 0.181636f;
	pVerts[105].ny = -0.250000f;
	pVerts[105].nz = -0.951057f;
	pVerts[105].u = 0.600000f;
	pVerts[105].v = 0.100000f;

	pVerts[106].x = 0.146946f;
	pVerts[106].y = -0.047746f;
	pVerts[106].z = -0.475528f;
	pVerts[106].nx = 0.293892f;
	pVerts[106].ny = -0.095491f;
	pVerts[106].nz = -0.951057f;
	pVerts[106].u = 0.700000f;
	pVerts[106].v = 0.100000f;

	pVerts[107].x = 0.146946f;
	pVerts[107].y = 0.047746f;
	pVerts[107].z = -0.475528f;
	pVerts[107].nx = 0.293892f;
	pVerts[107].ny = 0.095491f;
	pVerts[107].nz = -0.951057f;
	pVerts[107].u = 0.800000f;
	pVerts[107].v = 0.100000f;

	pVerts[108].x = 0.090818f;
	pVerts[108].y = 0.125000f;
	pVerts[108].z = -0.475528f;
	pVerts[108].nx = 0.181635f;
	pVerts[108].ny = 0.250000f;
	pVerts[108].nz = -0.951057f;
	pVerts[108].u = 0.900000f;
	pVerts[108].v = 0.100000f;

	pVerts[109].x = -0.000000f;
	pVerts[109].y = 0.154508f;
	pVerts[109].z = -0.475528f;
	pVerts[109].nx = -0.000000f;
	pVerts[109].ny = 0.309017f;
	pVerts[109].nz = -0.951057f;
	pVerts[109].u = 1.000000f;
	pVerts[109].v = 0.100000f;

	pVerts[110].x = 0.000000f;
	pVerts[110].y = -0.000000f;
	pVerts[110].z = -0.500000f;
	pVerts[110].nx = 0.000000f;
	pVerts[110].ny = -0.000000f;
	pVerts[110].nz = -1.000000f;
	pVerts[110].u = 0.000000f;
	pVerts[110].v = -0.000000f;

	pVerts[111].x = 0.000000f;
	pVerts[111].y = -0.000000f;
	pVerts[111].z = -0.500000f;
	pVerts[111].nx = 0.000000f;
	pVerts[111].ny = -0.000000f;
	pVerts[111].nz = -1.000000f;
	pVerts[111].u = 0.100000f;
	pVerts[111].v = -0.000000f;

	pVerts[112].x = 0.000000f;
	pVerts[112].y = -0.000000f;
	pVerts[112].z = -0.500000f;
	pVerts[112].nx = 0.000000f;
	pVerts[112].ny = -0.000000f;
	pVerts[112].nz = -1.000000f;
	pVerts[112].u = 0.200000f;
	pVerts[112].v = -0.000000f;

	pVerts[113].x = 0.000000f;
	pVerts[113].y = 0.000000f;
	pVerts[113].z = -0.500000f;
	pVerts[113].nx = 0.000000f;
	pVerts[113].ny = 0.000000f;
	pVerts[113].nz = -1.000000f;
	pVerts[113].u = 0.300000f;
	pVerts[113].v = -0.000000f;

	pVerts[114].x = 0.000000f;
	pVerts[114].y = 0.000000f;
	pVerts[114].z = -0.500000f;
	pVerts[114].nx = 0.000000f;
	pVerts[114].ny = 0.000000f;
	pVerts[114].nz = -1.000000f;
	pVerts[114].u = 0.400000f;
	pVerts[114].v = -0.000000f;

	pVerts[115].x = -0.000000f;
	pVerts[115].y = 0.000000f;
	pVerts[115].z = -0.500000f;
	pVerts[115].nx = -0.000000f;
	pVerts[115].ny = 0.000000f;
	pVerts[115].nz = -1.000000f;
	pVerts[115].u = 0.500000f;
	pVerts[115].v = -0.000000f;

	pVerts[116].x = -0.000000f;
	pVerts[116].y = 0.000000f;
	pVerts[116].z = -0.500000f;
	pVerts[116].nx = -0.000000f;
	pVerts[116].ny = 0.000000f;
	pVerts[116].nz = -1.000000f;
	pVerts[116].u = 0.600000f;
	pVerts[116].v = -0.000000f;

	pVerts[117].x = -0.000000f;
	pVerts[117].y = 0.000000f;
	pVerts[117].z = -0.500000f;
	pVerts[117].nx = -0.000000f;
	pVerts[117].ny = 0.000000f;
	pVerts[117].nz = -1.000000f;
	pVerts[117].u = 0.700000f;
	pVerts[117].v = -0.000000f;

	pVerts[118].x = -0.000000f;
	pVerts[118].y = -0.000000f;
	pVerts[118].z = -0.500000f;
	pVerts[118].nx = -0.000000f;
	pVerts[118].ny = -0.000000f;
	pVerts[118].nz = -1.000000f;
	pVerts[118].u = 0.800000f;
	pVerts[118].v = -0.000000f;

	pVerts[119].x = -0.000000f;
	pVerts[119].y = -0.000000f;
	pVerts[119].z = -0.500000f;
	pVerts[119].nx = -0.000000f;
	pVerts[119].ny = -0.000000f;
	pVerts[119].nz = -1.000000f;
	pVerts[119].u = 0.900000f;
	pVerts[119].v = -0.000000f;

	pVerts[120].x = 0.000000f;
	pVerts[120].y = -0.000000f;
	pVerts[120].z = -0.500000f;
	pVerts[120].nx = 0.000000f;
	pVerts[120].ny = -0.000000f;
	pVerts[120].nz = -1.000000f;
	pVerts[120].u = 1.000000f;
	pVerts[120].v = -0.000000f;

	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);

	// Create a VBO
	glGenBuffers(2, &this->vbo[0]);
	assert(this->vbo[0] != 0);
	// Load the combined data: ---------------------------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);


	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), pVerts, GL_STATIC_DRAW);

	// Vertext data in location 0
	void *offsetVert = (void *)((unsigned int)&pVerts[0].x - (unsigned int)pVerts);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);
	glEnableVertexAttribArray(0);

	// Texture data in location 1
	void *offsetTex = (void *)((unsigned int)&pVerts[0].u - (unsigned int)pVerts);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
	glEnableVertexAttribArray(1);

	// Normal data in location 2
	void *offsetNorm = (void *)((unsigned int)&pVerts[0].nx - (unsigned int)pVerts);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
	glEnableVertexAttribArray(2);


	// Load the index data: ---------------------------------------------------------

	// Bind our 2nd VBO as being the active buffer and storing index )
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	// Copy the index data to our buffer 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numtris), triList, GL_STATIC_DRAW);



}
