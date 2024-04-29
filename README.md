# familyprotect
各大游戏中的家人保护器，附带默认阴阳语料库
## background
相信各位都有在游戏时被队友或对手喷的体无完肤却无力回击的时候，本脚本旨在解决各大游戏中咱们这种老实玩家的痛点，让你拿起武器保护家人！
## how it works
本脚本不到1M，非常小，原理也很简单，随机从同目录下的data.txt语料库中选取一行复制进剪贴板，然后玩家只需要crtl+v到对话框里就好。如下图所示：
![9800b5662adcf4a0d4a1f79573df169](https://github.com/jidle123/familyprotect/assets/123531867/be6e415b-6ca7-4dce-b867-0759cb1a0dd1)

**安全性**：至于被检测到，各位老实玩家大可不必担心，这玩意和脚本有本质区别，和游戏接口没有直接交互，而剪贴板是windows系统公有的。可按如下理解：

![1714357803188](https://github.com/jidle123/familyprotect/assets/123531867/2748b8b4-2d70-448b-998c-f43f5c120590)

详细原理：使用了 <fstream> 来读取文件内容，并将每行存储在 std::vector<std::string> 中。然后，使用 C++11 的随机数引擎和分布来选择一个随机行。最后，使用 Windows API 来将选定的行复制到剪贴板。同时使用了 Windows API 函数 GetAsyncKeyState 来检测按键状态。在一个无限循环中，它会检测 F2 键和 F10 键的状态。当按下 F2 键时，将调用 copyRandomLineToClipboard 函数来随机复制一行到剪贴板。按下 F10 键时，程序将退出循环。
## how to use
1. 打开familyprotect.exe
2. 进入游戏
3. 按下F2保护家人，打开输入框crtl+v（有些游戏输入太快会被限制，如lol）
4. 保护完毕，f10退出
5. 如果看到了新的阴阳话想用，请在data.txt中新开一行填入保存即可
![1714358689251](https://github.com/jidle123/familyprotect/assets/123531867/94601259-bebd-4a38-bf55-343e576294fe)
## other
各位多多支持给个star，我也会自己维护默认语料库。
