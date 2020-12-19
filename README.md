# computer_graphics
Interactive Computer Graphics 를 공부

# VSC setting
> mac setting  

- [setting ref](https://code.visualstudio.com/docs/cpp/config-linux)



### build
```
shift + command + b
```

### debug
```
f5
```
- Continue  : 라인 단위 실행
- Step Over : 다음 브레이크 포인트
- Step into : 함수 진입
- Steop Out : 함수 탈출


- GLFW
```
C 로 작성된 라이브러리 
```


### task.json
```
tasks: 뒤에 오는 내용이 수행할 작업에 대한 내용
type: shell or process. shell 이면 command를 쉘 명령어로서 실행, process면 프로세스 실행인 것 같다.
label: 작업의 이름, 빌드 단축기 Ctrl+Shift+B 를 눌렀을 때 선택할 이름
command: 빌드를 실행할 컴파일러
args: command의 인자(파라미터)
- "-g": 디버깅을 위한 옵션
"${file}: 현재 파일을 의미
"-o": 출력파일의 이름을 정의해줄때 사용
"${fileDirname}/ ${fileBasenameNoExtension}": 파일의 현재 디렉토리에 파일명.out파일을 생성
cwd (Current Working Directory): 현재의 작업공간이다.
problemMatcher: 컴파일러마다 Warning이나 Error를 출력하는 규칙이 다르므로 출력 형식 지정해준다. 하지만 C/C++ Extention을 쓰기 때문에 자동으로 처리해준다. problemMatcher는 추가 설정 없이 "$gcc"로 설정하면, Extention에게 맡겨지게 된다. 자세한 내용은 Defining a problem matcher 참조
group: build or test. build면 빌드 명령어 (⌘(command) + ⇧(Shift) + B) 실행시 해당 task가 실행되고 test면 실행 명령을 내렸을 때 해당 task가 실행된다. "isDefault": true를 설정하면 빌드시 빌드 옵션을 선택하지 않고 바로 이 task를 실행한다.
```