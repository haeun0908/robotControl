# robotControl
이 프로그램은 아두이노를 활용해 휴머노이드 로봇을 제어하는 코드로, 초음파 센서와 조도 센서를 이용해 주변 환경을 감지하고 로봇의 동작을 자동으로 변경하는 기능을 수행합니다.<br>
버튼 입력을 통해 시작 여부를 조작할 수 있으며, LED와 서보모터를 사용하여 로봇의 상태를 표시하고 반응하게 합니다.

## 1. 하드웨어 연결
아두이노 보드에 초음파 센서, 조도 센서, 가변 저항, 버튼, LED, 서보모터, 그리고 시리얼 통신 모듈을 지정된 핀에 정확히 연결합니다.<br><br>
![하드웨어 연결](https://github.com/haeun0908/robotControl/blob/main/images/1.%20%ED%95%98%EB%93%9C%EC%9B%A8%EC%96%B4%20%EC%97%B0%EA%B2%B0.jpg)

## 2. 코드 업로드 
아두이노 IDE에서 robotControl.ino를 새 파일로 저장하고, 보드에 업로드합니다.<br><br>
![코드 업로드](https://github.com/haeun0908/robotControl/blob/main/images/2.%20%EC%BD%94%EB%93%9C%20%EC%97%85%EB%A1%9C%EB%93%9C.png)

## 3. 시리얼 모니터 활성화
아두이노 IDE에서 115200 baud rate로 시리얼 모니터를 열어 디버깅 메시지를 확인합니다.<br><br>
![시리얼 모니터 활성화](https://github.com/haeun0908/robotControl/blob/main/images/3.%20%EC%8B%9C%EB%A6%AC%EC%96%BC%20%EB%AA%A8%EB%8B%88%ED%84%B0%20%ED%99%9C%EC%84%B1%ED%99%94.png)

## 4. 센서 작동 확인
초음파 센서가 거리를 측정하고, 조도 센서가 주변 밝기를 감지하는지 시리얼 모니터에서 확인합니다.<br><br>
![센서 작동 확인](https://github.com/haeun0908/robotControl/blob/main/images/4.%20%EC%84%BC%EC%84%9C%20%EC%9E%91%EB%8F%99%20%ED%99%95%EC%9D%B8.png)

## 5. 자동 동작
로봇은 조도 센서 값을 통해 앉거나 일어서고, 초음파 센서 값을 이용해 주변 물체를 감지하여 다양한 동작을 수행합니다.
- 주변에 아무도 없거나 어두워지면 → 로봇이 앉아서 대기합니다.
- 100~150cm 내에 사람이 감지되면 → 로봇이 일어서서 대기합니다.
- 50~100cm 이내로 접근하면 → 인사를 수행합니다.
- 50cm 이하로 접근하면 → 전투태세를 갖춥니다.

![자동 동작](https://github.com/haeun0908/robotControl/blob/main/images/5.%20%EC%9E%90%EB%8F%99%20%EB%8F%99%EC%9E%91.gif)
