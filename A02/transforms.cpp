	// Translate of +2 on the x axis, and -1 on the y axis
	const float MT1[] =  {
			   1.0,		0.0,		0.0,		2.0,
			   0.0,		1.0,		0.0,		-1.0,
			   0.0,		0.0,		1.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Rotate of 45 degrees on the x axis
	const float MT2[] =  {
			   1.0,		0.0,		0.0,		0.0,
			   0.0,		0.707106781,		-0.707106781,		0.0,
			   0.0,		0.707106781,		0.707106781,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Make the object 2 times smaller
	const float MT3[] =  {
			   2.0,		0.0,		0.0,		0.0,
			   0.0,		2.0,		0.0,		0.0,
			   0.0,		0.0,		2.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Make the object 2 times longer on the z axis, and half on the other axis
	const float MT4[] =  {
			   0.5,		0.0,		0.0,		0.0,
			   0.0,		0.5,		0.0,		0.0,
			   0.0,		0.0,		2.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};

	// Mirror over the z axis
	const float MT5[] =  {
			   -1.0,		0.0,		0.0,		0.0,
			   0.0,		-1.0,		0.0,		0.0,
			   0.0,		0.0,		1.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};
			   
	// Flatten over the z axis
	const float MT6[] =  {
			   1.0,		0.0,		0.0,		0.0,
			   0.0,		1.0,		0.0,		0.0,
			   0.0,		0.0,		0.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};

	// Make a shear along the Y axis, with a factor of 1 along the x axis
	const float MT7[] =  {
			   1.0,		1.0,		0.0,		0.0,
			   0.0,		1.0,		0.0,		0.0,
			   0.0,		0.0,		1.0,		0.0,
			   0.0,		0.0,		0.0,		1.0};
