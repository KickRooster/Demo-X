#include "TextGameDataManager.h"

// 辅助宏：简化节点创建
#define ADD_NODE(Id, Text) \
	{ FTextGameNode Node; Node.Content = FText::FromString(TEXT(Text));

#define ADD_OPTION(OptId, OptText, NextId) \
	{ FTextGameOption Opt; Opt.OptionId = NextId; Opt.OptionText = FText::FromString(TEXT(OptText)); Node.Options.Add(Opt); }

#define END_NODE() Nodes.Add(Id, Node); }

void UTextGameDataManager::Init()
{
	Nodes.Empty();

	// === 第1步：开场 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"你在一片漆黑中醒来。空气潮湿而冰冷，远处传来水滴落在石面上的回声。"
			"你摸索着站起身，脚下是粗糙的石板地面。微弱的光从前方隧道尽头透出。"
		));
		FTextGameOption O1; O1.OptionId = 1; O1.OptionText = FText::FromString(TEXT("向光源走去"));
		FTextGameOption O2; O2.OptionId = 2; O2.OptionText = FText::FromString(TEXT("原地等待，让眼睛适应黑暗"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Nodes.Add(0, Node);
	}

	// === 第2步：向光源走去 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"你沿着隧道小心翼翼地前行。光线逐渐变亮，你发现自己来到了一个巨大的地下洞穴。"
			"洞穴中央有一座古老的石桥横跨在深不见底的裂缝之上。桥的另一端有两扇门——"
			"一扇是锈迹斑斑的铁门，另一扇是雕刻着奇异符文的木门。"
		));
		FTextGameOption O1; O1.OptionId = 3; O1.OptionText = FText::FromString(TEXT("走过石桥，推开铁门"));
		FTextGameOption O2; O2.OptionId = 4; O2.OptionText = FText::FromString(TEXT("走过石桥，推开木门"));
		FTextGameOption O3; O3.OptionId = 5; O3.OptionText = FText::FromString(TEXT("检查桥下的裂缝"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Node.Options.Add(O3);
		Nodes.Add(1, Node);
	}

	// === 第3步：原地等待 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"你蹲下身，闭上眼睛，静静等待。渐渐地，你的眼睛适应了黑暗。"
			"你发现身后的墙壁上有一行发光的文字：「勇者不惧黑暗，智者善用黑暗。」"
			"文字下方有一个隐藏的凹槽，里面放着一把生锈的钥匙和一支火把。"
		));
		FTextGameOption O1; O1.OptionId = 6; O1.OptionText = FText::FromString(TEXT("拿起钥匙和火把，向前走"));
		FTextGameOption O2; O2.OptionId = 1; O2.OptionText = FText::FromString(TEXT("只拿火把，向光源走去"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Nodes.Add(2, Node);
	}

	// === 第4步：铁门 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"铁门发出刺耳的尖叫声，缓缓打开。门后是一间废弃的铸造车间。"
			"炉火早已熄灭，但空气中仍残留着金属的气味。工作台上散落着各种工具，"
			"角落里有一副破旧的铠甲，胸口处刻着一个你从未见过的徽章。"
		));
		FTextGameOption O1; O1.OptionId = 7; O1.OptionText = FText::FromString(TEXT("穿上铠甲"));
		FTextGameOption O2; O2.OptionId = 8; O2.OptionText = FText::FromString(TEXT("检查工作台上的工具"));
		FTextGameOption O3; O3.OptionId = 9; O3.OptionText = FText::FromString(TEXT("继续向车间深处探索"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Node.Options.Add(O3);
		Nodes.Add(3, Node);
	}

	// === 第5步：木门 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"木门上的符文在你触碰的瞬间亮起蓝光，门无声地滑开。"
			"门后是一座地下图书馆，书架高耸入穹顶，数不清的书籍整齐排列。"
			"一位白发老者坐在中央的书桌前，似乎一直在等你。"
			"「你终于来了，」他抬起头，眼中闪烁着智慧的光芒，「我有三个问题要问你。」"
		));
		FTextGameOption O1; O1.OptionId = 10; O1.OptionText = FText::FromString(TEXT("「请问吧。」"));
		FTextGameOption O2; O2.OptionId = 11; O2.OptionText = FText::FromString(TEXT("「你是谁？为什么在这里？」"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Nodes.Add(4, Node);
	}

	// === 第6步：检查裂缝 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"你趴在桥边向下望去。裂缝深不见底，但你注意到裂缝壁上有一排铁钉，"
			"形成了一条通往下方的简易阶梯。大约十米深处有一个洞口，隐约透出暖黄色的光。"
			"这条路看起来很危险，但也许通向一个不为人知的地方。"
		));
		FTextGameOption O1; O1.OptionId = 12; O1.OptionText = FText::FromString(TEXT("沿铁钉向下攀爬"));
		FTextGameOption O2; O2.OptionId = 3; O2.OptionText = FText::FromString(TEXT("太危险了，还是去铁门"));
		FTextGameOption O3; O3.OptionId = 4; O3.OptionText = FText::FromString(TEXT("太危险了，还是去木门"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Node.Options.Add(O3);
		Nodes.Add(5, Node);
	}

	// === 第7步：带钥匙前进 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"火把照亮了隧道，你发现墙壁上画满了壁画——描绘着一个古老文明的兴衰。"
			"你来到了同样的地下洞穴，但借助火光，你发现石桥旁边还有第三条路："
			"一条狭窄的石阶通向上方，尽头有一扇上了锁的门。你手中的钥匙似乎正好合适。"
		));
		FTextGameOption O1; O1.OptionId = 13; O1.OptionText = FText::FromString(TEXT("用钥匙打开上方的门"));
		FTextGameOption O2; O2.OptionId = 3; O2.OptionText = FText::FromString(TEXT("忽略石阶，去铁门"));
		FTextGameOption O3; O3.OptionId = 4; O3.OptionText = FText::FromString(TEXT("忽略石阶，去木门"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Node.Options.Add(O3);
		Nodes.Add(6, Node);
	}

	// === 第8步：穿上铠甲 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"铠甲出奇地合身。穿上的瞬间，你感到一股力量涌入体内。"
			"胸口的徽章发出微光，车间深处的一面墙壁缓缓升起，露出一条密道。"
			"密道中传来低沉的咆哮声，似乎有什么东西在里面等待。"
		));
		FTextGameOption O1; O1.OptionId = 14; O1.OptionText = FText::FromString(TEXT("穿着铠甲进入密道"));
		FTextGameOption O2; O2.OptionId = 8; O2.OptionText = FText::FromString(TEXT("先去工作台找件武器"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Nodes.Add(7, Node);
	}

	// === 第9步：检查工具 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"工作台上有一把锤子、一把钳子和一柄短剑。短剑虽然有些钝了，"
			"但握在手中仍然很趁手。你还发现了一张泛黄的地图，"
			"上面标注了这个地下迷宫的部分路线，其中一条路标着「出口」。"
		));
		FTextGameOption O1; O1.OptionId = 14; O1.OptionText = FText::FromString(TEXT("拿起短剑，进入密道"));
		FTextGameOption O2; O2.OptionId = 15; O2.OptionText = FText::FromString(TEXT("按地图指示寻找出口"));
		FTextGameOption O3; O3.OptionId = 7; O3.OptionText = FText::FromString(TEXT("先穿上角落的铠甲"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Node.Options.Add(O3);
		Nodes.Add(8, Node);
	}

	// === 第10步：车间深处 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"车间深处越来越暗。你摸索着前进，突然脚下一空——你踩到了一个机关！"
			"地板翻转，你滑入一条光滑的石质滑道，急速下坠。"
			"几秒后你落入一个柔软的沙堆中，抬头一看，这是一个圆形竞技场。"
			"对面的铁栅栏后，一双红色的眼睛正盯着你。"
		));
		FTextGameOption O1; O1.OptionId = 14; O1.OptionText = FText::FromString(TEXT("准备战斗"));
		FTextGameOption O2; O2.OptionId = 16; O2.OptionText = FText::FromString(TEXT("寻找竞技场的出口"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Nodes.Add(9, Node);
	}

	// === 第11步：老者的问题 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"老者微笑着说：「第一个问题——你为何来到这里？」"
			"他的声音平静而深沉，仿佛这个问题的答案比你想象的更重要。"
		));
		FTextGameOption O1; O1.OptionId = 17; O1.OptionText = FText::FromString(TEXT("「我不知道，我醒来就在这里了。」"));
		FTextGameOption O2; O2.OptionId = 17; O2.OptionText = FText::FromString(TEXT("「我在寻找出路。」"));
		FTextGameOption O3; O3.OptionId = 17; O3.OptionText = FText::FromString(TEXT("「也许是命运指引我来的。」"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Node.Options.Add(O3);
		Nodes.Add(10, Node);
	}

	// === 第12步：质问老者 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"老者放下手中的书，叹了口气。「我是这座图书馆的守护者，已经在这里等了很久。"
			"这里记载着所有进入迷宫之人的故事——包括你的。」"
			"他指了指身后的一本打开的书，上面正在书写着你此刻的经历。"
		));
		FTextGameOption O1; O1.OptionId = 10; O1.OptionText = FText::FromString(TEXT("「好吧，请问你的问题。」"));
		FTextGameOption O2; O2.OptionId = 18; O2.OptionText = FText::FromString(TEXT("翻看那本记录你故事的书"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Nodes.Add(11, Node);
	}

	// === 第13步：攀爬裂缝 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"你小心翼翼地踩着铁钉向下攀爬。风从裂缝深处呼啸而上，吹得你几乎站不稳。"
			"终于，你到达了那个洞口。里面是一个温暖的小房间，"
			"墙上挂着火把，中央有一口古井。井水清澈见底，水面映出的不是你的倒影，"
			"而是一片星空。"
		));
		FTextGameOption O1; O1.OptionId = 19; O1.OptionText = FText::FromString(TEXT("喝一口井水"));
		FTextGameOption O2; O2.OptionId = 20; O2.OptionText = FText::FromString(TEXT("向井中投入一枚石子"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Nodes.Add(12, Node);
	}

	// === 第14步：钥匙开门 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"钥匙完美地插入锁孔，门「咔嗒」一声打开。门后是一条通往地面的阶梯，"
			"你能感受到新鲜的空气和阳光的温度。你终于找到了出口！"
			"但在踏出最后一步之前，你回头望了一眼身后的黑暗——"
			"这段旅程改变了你，你已经不再是醒来时的那个人了。"
		));
		FTextGameOption O1; O1.OptionId = -1; O1.OptionText = FText::FromString(TEXT("走向阳光（结局A：自由）"));
		Node.Options.Add(O1);
		Nodes.Add(13, Node);
	}

	// === 第15步：密道战斗 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"密道中的咆哮声越来越近。一只巨大的石像鬼从黑暗中扑来！"
			"你本能地举起双臂防御。铠甲上的徽章爆发出耀眼的光芒，"
			"石像鬼发出痛苦的嘶吼，化为碎石散落一地。"
			"在碎石中，你发现了一颗散发着柔和光芒的宝石。"
		));
		FTextGameOption O1; O1.OptionId = -1; O1.OptionText = FText::FromString(TEXT("拾起宝石（结局B：力量）"));
		Node.Options.Add(O1);
		Nodes.Add(14, Node);
	}

	// === 第16步：按地图找出口 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"你按照地图上的标注，穿过一条又一条走廊。地图非常精确，"
			"每一个转弯、每一个岔路都标注得清清楚楚。"
			"最终你来到一扇标着「出口」的门前，门上写着：「知识是最好的武器。」"
		));
		FTextGameOption O1; O1.OptionId = -1; O1.OptionText = FText::FromString(TEXT("推门离开（结局C：智慧）"));
		Node.Options.Add(O1);
		Nodes.Add(15, Node);
	}

	// === 第17步：竞技场出口 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"你环顾四周，发现竞技场的看台上有一扇小门。"
			"你飞快地爬上看台，在那双红色眼睛的主人冲出铁栅栏之前，"
			"钻进了小门。门后是一条向上的螺旋楼梯，你拼命奔跑，"
			"身后传来愤怒的咆哮声，但越来越远了。"
		));
		FTextGameOption O1; O1.OptionId = -1; O1.OptionText = FText::FromString(TEXT("逃出生天（结局D：生存）"));
		Node.Options.Add(O1);
		Nodes.Add(16, Node);
	}

	// === 第18步：老者的考验 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"老者点了点头：「不错的回答。第二个问题——如果你能带走这里的一样东西，你会选什么？」"
			"他挥了挥手，书架上飞出三样东西悬浮在你面前：一本古书、一把钥匙、一面镜子。"
		));
		FTextGameOption O1; O1.OptionId = -1; O1.OptionText = FText::FromString(TEXT("选择古书（结局E：知识）"));
		FTextGameOption O2; O2.OptionId = 13; O2.OptionText = FText::FromString(TEXT("选择钥匙"));
		FTextGameOption O3; O3.OptionId = -1; O3.OptionText = FText::FromString(TEXT("选择镜子（结局F：真相）"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Node.Options.Add(O3);
		Nodes.Add(17, Node);
	}

	// === 第19步：翻看故事书 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"你走到书桌前翻看那本书。书页上的文字正在实时书写着你的一举一动——"
			"「他走到书桌前，翻开了记录自己命运的书……」"
			"你感到一阵眩晕，文字开始模糊，书页翻涌。当你回过神来，"
			"你发现自己站在迷宫的入口，一切似乎重新开始了。但你的记忆还在。"
		));
		FTextGameOption O1; O1.OptionId = 0; O1.OptionText = FText::FromString(TEXT("带着记忆重新开始"));
		FTextGameOption O2; O2.OptionId = -1; O2.OptionText = FText::FromString(TEXT("合上书本（结局G：轮回）"));
		Node.Options.Add(O1);
		Node.Options.Add(O2);
		Nodes.Add(18, Node);
	}

	// === 第20步：喝井水 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"井水冰凉甘甜。喝下的瞬间，你的脑海中涌入了无数画面——"
			"这座迷宫的历史、建造者的故事、以及所有曾经迷失在这里的灵魂。"
			"你获得了理解这个地方的能力。井水的星空倒影化为一道光柱，"
			"将你缓缓托起，送向地面。"
		));
		FTextGameOption O1; O1.OptionId = -1; O1.OptionText = FText::FromString(TEXT("随光而去（结局H：觉醒）"));
		Node.Options.Add(O1);
		Nodes.Add(19, Node);
	}

	// === 第21步：投石入井 ===
	{
		FTextGameNode Node;
		Node.Content = FText::FromString(TEXT(
			"石子落入井中，水面的星空泛起涟漪。涟漪扩散，整个房间开始震动。"
			"井水上涨，从井口溢出，但那不是普通的水——是液态的星光。"
			"星光淹没了你的脚踝、膝盖、腰部……你没有感到恐惧，反而感到前所未有的平静。"
			"当星光没过头顶时，你发现自己漂浮在一片真正的星空中。"
		));
		FTextGameOption O1; O1.OptionId = -1; O1.OptionText = FText::FromString(TEXT("融入星空（结局I：永恒）"));
		Node.Options.Add(O1);
		Nodes.Add(20, Node);
	}
}

bool UTextGameDataManager::GetNode(int32 NodeId, FTextGameNode& OutNode) const
{
	const FTextGameNode* Found = Nodes.Find(NodeId);
	if (Found)
	{
		OutNode = *Found;
		return true;
	}
	return false;
}

#undef ADD_NODE
#undef ADD_OPTION
#undef END_NODE
