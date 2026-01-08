# Bounce

## 📖 소개
- 패들바를 이용해서 공을 쳐낼시 점수를 획득
- 공이 하단의 화면 밖으로 나가면 Live가 삭감
- 점수를 쌓으면 text파일에 저장되어 다음 게임 화면에 출력

## 📂 폴더 구조
- .vscode/   : Debug
- Contents/  : 이미지, 사운드 등 리소스
- Source/    : 소스 코드
- include/   : 헤더 파일
- Build/     : CMAKE 빌드 결과물

## ⚙️ 환경 설정

- CMake 3.28 이상
- Git 설치 필요
- SFML 3.0.2 (FetchContent로 자동 다운로드)

## 🚀 빌드 방법

```bash
cmake -B Build -D CMAKE_BUILD_TYPE=Debug
cmake --build Build --config Debug -j
```
