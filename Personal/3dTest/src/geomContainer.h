typedef struct geomContainer{
	int nVerts, nIndices, nTexCoords, nSubCols, indices[];
	float vertices[], texCoords[];
} geomContainer;

geomContainer getSquare(){
	geomContainer square;
	square.nVerts = 4;
	square.vertices = std::initializer_list<float>({0.f, 0.f, 40.f, 0.f, 0.f, 40.f, 40.f, 40.f});
	square.nIndices = 4;
	square.indices = {0, 1, 2, 3};
	square.nTexCoords = 4;
	square.texCoords = {0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f};
}
