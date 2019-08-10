# Electronic_Car_Project
본 프로젝트는 수원하이텍고등학교 학생들이 예산을 지원받아 제작하는 '전기차 제작 프로젝트'입니다.
이 저장소에는 전기차에 탑재될 후방감지기, 화재감지기, 긴급 제동장치등의 코드가 업로드됩니다.

각각의 코드는 기기 하나당 MCU보드 1개를 사용하는 것을 기준으로 만들어졌으며 이후에 통합 버전을 업로드할 예정입니다.

제작자 : 수원하이텍고등학교 3학년 김민규, 김민기, 김종국, 남윤재, 배한결

텔레그램 급식알리미 : 
* 제품 구상 시작 - 2019.03.13
* 재료 1차 신청 - 2019.0
* 알파버전 완성 - 2019.07.25
* 알파버전 테스트 - 2019.07.26
* 코드 간결화(일부) - 2019.08.01

카카오 플러스 친구 급식알리미 :
* kakao i developers 접근권한 신청 - 2019.07.25
* kakao i developers 접근권한 허가 - 2019.07.26
* 제작중...(2019.08.05 현재)

기능으로는 "그제, 어제, 오늘, 내일, 모레"와 "start"가 존재합니다.

* start명령어는 봇이 동작하는지 확인할 수 있습니다.
* 나머지 명령어는 각각 당일 기준으로 해당 날짜 수원하이텍고등학교의 급식표를 가져옵니다.(단, 아침 메뉴는 업체 미제공으로 지원 불가)

급식표 주소 : 'http://sht.hs.kr/?_page=41&_action=view&_view=view&yy=' + str(today.year) + '&mm=' + str(today.month) + '&dd=' + str(today.day)
