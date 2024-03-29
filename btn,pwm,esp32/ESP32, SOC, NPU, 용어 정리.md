

시리얼 모니터 결과 확인 - >
ctrl + shift + M

<details>
<summary>PWM 제어에서 LED 채널이 무엇인지?
</summary>


channel 당 하나의 제품을 제어한다고 보시면 됩니다.
마치 cpu 코어 개수 같은 개념이라


순서대로 임의로 부여해서 사용하면 되는 것인가요?


channel 이 몇 개 지원하냐에 따라 몇 개의 PWM 제어를 별도로 제어할 수 있는가 를 나타냅니다
 0부터 채워 넣는 게 낫겠죠



혹시 몇번까지 있는지는
어떻게 알 수 있나요?


https://www.upesy.com/blogs/tutorials/esp32-pinout-reference-gpio-pins-ultimate-guide
18개까지 지원이 된다고 나와있습니다

</details>

16:17

[아두이노 DOC](https://www.arduino.cc/reference/ko/)

map 함수, constrain 함수가 굉장히 유용하여 알아두는 것이 좋습니다

<hr>

## ESP 32
웹 서버로서 동작이 가능합니다

주의사항!
built in led 를 사용하더라도 
pin Mode로 설정해주어야 동작합니다!
```ino
void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
    digitalWrite(LED_BUILTIN,HIGH);
}
```

<hr>

엣지 컴퓨팅 기술이란?
말단에 있는 장비가 통신이 끊겨도 작동을 유지하다가 
통신이 재개되면 서버로 데이터를 전송

edge node라는 중간 노드가 존재합니다.

용어 정리
### SoC

System on Chip
전체 시스템을 칩 하나에 담은 기술집약적 반도체. 
여러 기능을 가진 기기들로 구성된 시스템을 하나의 칩으로 만드는 기술입니다. 연산 소자 (CPU), 메모리 소자(D램, 플래시 등), 디지털신호처리 소자(DSP) 등 주요 반도체 소자를 하나의 칩에 구현하여 칩 자체가 하나의 시스템이 되도록 하는 것입니다.

즉 PCB(Printed Circuit Board)상에서 여러 개의 반도체 칩이 모여 구현되던 시스템이 한 개의 칩으로 집적되는 기술을 의미합니다.

이렇게 여러 기능을 가진 반도체가 하나의 칩으로 통합되면 칩을 탑재하는 공간이 크게 줄어들어 제품 소형화가 가능하고, 여러 개의 반도체를 별도로 만드느는 것 개비 제조비용일 감소하는 등 여러 장점들이 있습니다.

출처: 삼성전자 반도체 뉴스룸


### NPU

Neural Processing Unit, 신경망 처리장치는 딥러닝 알고리즘 연산에 최적화된 프로세서로, 빅데이터를 사람의 신경망처럼 빠르고 효율적으로 처리할 수 있습니다. 이러한 특징 때문에 AI 연산에 주로 활용됩니다.
스마트폰 카메라로 사진을 찍을 때 배경 안의 사물, 환경, 인물을 의식해 자동으로 초점을 조정하는 것, 음식 사진 촬영 시 카메라가 음식 모드로 자동 전환되는 것, 촬영된 결과물에서 불필요한 피사체만 지울 수 있는 것도 모두 NPU 덕분입니다.

출처: [삼성 뉴스룸](https://news.samsung.com/kr/%EC%97%91%EC%8B%9C%EB%85%B8%EC%8A%A4-%EA%B0%9C%EB%B0%9C-%EB%A6%AC%EB%8D%94%EB%93%A4%EC%9D%B4-soc%EB%A5%BC-%EB%A7%90%ED%95%98%EB%8B%A4-%E2%91%A1-cpu-%C2%B7-npu-%EC%95%8C%EC%95%84)

### 포그 컴퓨팅

포그 컴퓨팅은 엣지 컴퓨팅과 유사합니다. 차이점은 엣지 컴퓨팅이 네트워크의 말단에서 데이터를 처리하는 반면, 포그 컴퓨팅은 장치의 로컬 영역 네트워크에서 데이터를 처리한다는 것입니다. 포그 컴퓨팅은 엣지 컴퓨팅에 비해 더 많은 데이터를 처리한다는 강점이 있지만 네트워크 내에서 물리적으로 연결된 기기들에 국한된다는 한계가 있습니다.

출처: [nvidia 블로그](https://blogs.nvidia.co.kr/2021/01/26/what-is-edge-computing/)

