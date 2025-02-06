#include <fbxsdk.h>

using namespace fbxsdk;

int main(int args, char* argv[])
{
    FbxManager* manager = FbxManager::Create();

    if(!manager){
        printf("failed to load fbxsdk\n");
    }
    
    
    FbxScene* scene = FbxScene::Create(manager, "MyScene");
    FbxImporter* importer = FbxImporter::Create(manager, "");
    
    if (importer->Initialize("model.fbx", -1, manager->GetIOSettings())) {
        importer->Import(scene);
        importer->Destroy();
        // 씬 데이터 처리 로직
    }
    
    manager->Destroy();
    

    system("pause");

    return 0;
}

