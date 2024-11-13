export SDK_DIR=$1


cd ${SDK_DIR}
wget https://github.com/opencv/opencv/releases/download/4.10.0/opencv-4.10.0-android-sdk.zip && unzip opencv-4.10.0-android-sdk.zip

mkdir -p libraries/include/ && cd libraries/include/ && wget https://github.com/google-ar/arcore-android-sdk/blob/main/libraries/include/arcore_c_api.h 
cd ${SDK_DIR}
mkdir -p third_party && git clone https://github.com/g-truc/glm.git && mv glm/glm third_party/

cd ${SDK_DIR}
git clone https://github.com/intelav/ARapp.git

chmod 777 ARapp/gradlew 

ARapp/gradlew build --project-dir=ARapp/app -POpenCVDir=${SDK_DIR}/Opencv-android-sdk/sdk/native/jni 

