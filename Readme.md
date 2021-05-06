Trần Minh Dương  - 20021323
* Folder bomman là quá trình làm game, Wizard In Dungeon là thành quả cuối
* Video: https://youtu.be/14fKrETxk1Y
  link dự phòng: https://drive.google.com/file/d/16UtWWIYe_PQfA-P4kUHtchielCw4b1AY/view?usp=sharing
* Giới thiệu: Trong Wizard In Dungeon, bạn là một phù thủy đang bị lạc trong ngục tối, phải tiêu diệt hết quái vật và tìm lối ra. 
* Ý tưởng: Khi đang làm Bomberman thì em chuyển hướng sang game này, từ đó em tự nghĩ cốt truyện, bối cảnh.
* Tính năng: (cụ thể trong video)
   - Menu với 3 nút Play, Help, Exit, có thể tạm dừng khi chơi
   - Game có 2 màn chơi, 1 màn quái thường và 1 màn boss
   - Hình ảnh: rõ ràng,
   - Có 4 chuyển cảnh: 1 khi qua màn đầu, 2 khi thua và 1 khi thắng
   - Âm thanh: game có đầy đủ âm thanh : khi click trong menu, nhạc nền, đạn bắn, âm thanh khi nhân vật chết, âm thanh khi thắng/thua
* Về vấn đề tham khảo:
   - Em có học cách làm game từ series: https://www.youtube.com/watch?v=q1WzniyeGTU&list=PLR7NDiX0QsfTIEQUeYCfc2MyCquX0ig9V 
từ kênh "Phát Triển Phần Mềm 123A-Z" nên cách triển khai khá giống. 
   - Về phần code:
    + BaseObject, Map, ImpTimer, TextObject: là các class em học từ series trên
    + PlayerObject, EnemyObject, BulletObject: em tham khảo và có điều chỉnh lại, code thêm.
    + BossObject : tự code, phát triển trên cơ sở EnemyObject.
    + Button và Menu: Hàm LButton em lấy từ Lazyfoo, chỉnh sửa để kết hợp với BaseObject, sau đó Menu em tự làm.
    + Game.h : Collision lấy từ Lazyfoo, các hàm menu, chuyển cảnh em tự viết
* Về nguồn hình ảnh, âm thanh
    - Các sprite nhân vật, quân địch lấy từ các nguồn free trên itch.io, sau đó tự edit lại
    - Menu, scene chuyển cảnh: tự edit, các thành phần thì lấy trên mạng
    - Âm thanh: 
        + Các Chunk: từ trang freesoundseffect, 1 số là từ game mario
        + 3 bản nhạc nền: là Unravel -Tokyo Ghoul OP,  Pokemon Battle(Vs trainer) theme song ; DarthVader Theme song
* Điểm số:
    Em xin tự đánh giá game với mức điểm 9+.
 
