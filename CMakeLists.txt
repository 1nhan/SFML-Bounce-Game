cmake_minimum_required(VERSION 3.28)

project(Bounce CXX)

include(FetchContent)
FetchContent_Declare(
    sfml GIT_REPOSITORY 
    https://github.com/SFML/SFML.git 
    GIT_TAG 3.0.2
    )
FetchContent_MakeAvailable(sfml)

# file: Source/폴더내 모든 .cpp파일을 수집하도록 요청
# GLOB은 특정 패턴과 일치하는 file을 검색한다는 의미
# SOURCES는 file이름을 저장하는 변수
# CONFIGURE_DEPENDS 프로젝트에 파일이 추가되거나 제거될 때마다 CMAKE가 자체적으로 재구성하도록 구성 종속 항목을 추가
# Source/*.cpp 이 폴더에 있는 모든 CPP를 찾도록 지시한다.
# 빌드하려는 실행 파일의 이름을 정의 
file(GLOB SOURCES CONFIGURE_DEPENDS Source/*.cpp)

add_executable(Bounce ${SOURCES})

target_include_directories(Bounce PRIVATE Include)
target_compile_features(Bounce PRIVATE cxx_std_20)
target_link_libraries(Bounce PRIVATE SFML::Graphics SFML::Audio)
