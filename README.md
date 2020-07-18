# cub3d_Raycasting

Raycasting의 이해
------------------
**벽 감지**  
<img src="/attachments/60e95e54-a1e7-45e0-86b1-1da33d237630" width="150" height="150">  
빨간 라인 위 빨간 점에서 벽이 감지되지 않으면, 특정 값을 더해 다음 점에서 벽이 감지되는지 확인한다.  
위의 그림은, 빨간 점이 파란색 위에 있지 않기 때문에 벽을 감지하지 못하는 경우이다.  
<img src="/attachments/de1b5aae-894b-48f9-9ecc-9ccbfa221340" width="150" height="150">  
이를 방지하기 위해, 빨간 라인이 x좌표에 닿을 때마다 벽을 체크하면 정확하게 벽을 찾을 수 있다.  
--> DDA(Digital Differential Analysis) 알고리즘 사용.  
      
**플레이어의 방향**  
방향을 벡터로 나타내기 위해 x, y 좌표로 방향을 표현한다.  
플레이어의 위치를 통해 플레이어가 보는 방향으로 선을 그리면, 라인의 모든 점들은 (플레이어 위치 + 방향벡터의 곱)이다.  
방향벡터의 길이는 실제로 중요하지 않고 방향만 중요하다. 방향벡터 x,y를 곱하면 길이는 변하지만 방향은 변하지 않는다.  
      
**camera plane vector**  
3D 엔진에서 3D평면을 표현하기 위해서는 camera plane vector와 방향벡터(u와 v)가 있어야 한다.  
하지만 raycasting은 2D이므로 camera plane은 실제로 평면이 아니라 선=단일벡터로 표시된다.  
여기서 camera plane은 컴퓨터 화면의 표면을 나타내고, camera plane은 항상 방향벡터와 수직이어야 한다.(camera plane ㅗ direction vector)  
방향벡터는 화면 내부를 의미한다.  
<img src="/attachments/b1b7a178-323e-4582-9d2a-a216f5d46af1" width="200" height="200">  
여기서 녹색 점은 플레이어의 위치이고 벡터 pos로 표현한다.  
검은 선은 방향벡터 이므로 검은 점의 위치는 pos + dir이다.  
파란 선은 전체 camera plane을 의미한다. 검은 점에서 오른쪽 파란 점까지의 벡터는 평면 벡터를 나타내므로 pos + dir + plane으로 표현할 수 있다.  
왼쪽 점도 마찬가지로 위치를 pos + dir - plane으로 표현할 수 있다.  
      
      
예를 들어 위 그림에서, 세번째 빨간 라인은 camera plane을 통과한다.  
라인이 평면을 통과하는 점은 plane의 오른쪽 1/3 부분에 위치한다.  
따라서 이 빨간 라인의 방향은 dir + plane * 1/3이다.  
이 라인의 방향벡터는 rayDir라 하고, 이 벡터의 x,y는 DDA 알고리즘에서 사용된다.  

**FOV**  
camera plane의 양 끝과 닿는 두 선 사이의 각도를 FOV라고 한다.  
FOV는 방향벡터의 길이와 plane 길이의 비울에 의해 결정된다.  
<img src="/attachments/6b8ee5a8-d2b9-4a2b-af23-7e16fe43d796" width="150" height="150">  


    방향벡터 길이 =  camera plane vector 길이 일때,  
    FOV = 90도  
<img src="/attachments/29167ccf-7304-4b36-adec-a843748e0a7e" width="100" height="200">  


    방향벡터 길이 >  camera plane vector 길이 일때,  
    FOV < 90도  
    (narrow) 좁게 보인다 = 크게 조금 보인다 = 확대했을 때와 같음      
<img src="/attachments/6eedbff5-6de6-4641-9b65-b5dc9883dd7e" width="200" height="100">  


    방향벡터 길이 <  camera plane vector의 길이,  
    FOV > 90도  
    (Wide) 넓게 보인다 = 작게 많이 보인다 = 축소했을 때와 같음  


**회전**  
플레이어가 회전하면 방향벡터와 평면벡터 모두 회전해야한다.  
그러면 빨간 라인은 모두 자동으로 회전된다.  
<img src="/attachments/6c310389-7517-4fab-a0a8-939a9d621b23" width="200" height="200">  
벡터를 회전하기 위해서는 회전 행렬과 곱해야 한다.  
<img src="/attachments/2131ce30-cb33-4042-b7f2-d69d3d84c10f" width="200" height="200">  
<img src="/attachments/7cc0ada2-8f74-4223-8041-e8093289684c" width="200" height="50">  
x, y 좌표를 x', y' 좌표로 회전할 수 있다.  
    

