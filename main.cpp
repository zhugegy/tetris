// 项目俄罗斯方块.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "main.h"
#include <time.h>

#include "interface.h"
#include "play_solo.h"
#include "customize_blocks.h"
#include "file_operator.h"
#include "chain_list_processor.h"
#include "data_processor.h"
#include "play_vs_com.h"
#include "main_menu.h"

static int initialize_parameter(Param *pstParam);
static int initialize_environment();

int _tmain(int argc, _TCHAR* argv[])
{
  Param stMainParam;    //主要参数结构体

  //初始化参数
  initialize_parameter(&stMainParam);

  //初始化界面环境
  initialize_environment();

  //程序主循环
  while (stMainParam.eStageFlag != STAGE_QUIT)
  {
    system("cls");
    //改变界面风格
    change_interface_style__interface(stMainParam.eStageFlag);

    switch (stMainParam.eStageFlag)
    {
    case STAGE_MAIN_MENU:
      main_menu(&stMainParam);
      break;
    case STAGE_PLAY_SOLO:
      play_solo(&stMainParam);
      break;
    case STAGE_CUSTOMIZE_BLOCKS:
      customize_blocks(&stMainParam);
      break;
    case STAGE_PLAY_VS_COM:
      play_vs_com(&stMainParam);
      break;
    default:
      break;
    }
  }

  return 0;
}

static int initialize_parameter(Param *pstParam)
{
  int i = 0;
  
  //初始随机数种子
  srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样

  //初始化舞台
  //pstParam->eStageFlag = stage_main_menu;
  //debug
  //pstParam->eStageFlag = STAGE_PLAY_SOLO;
  //pstParam->eStageFlag = STAGE_CUSTOMIZE_BLOCKS;
  //pstParam->eStageFlag = STAGE_PLAY_VS_COM;
  pstParam->eStageFlag = STAGE_MAIN_MENU;


  //初始化俄罗斯方块方阵（玩家）
  memset(pstParam->TetrisPlaySpacePlayer, 0, 
    sizeof(pstParam->TetrisPlaySpacePlayer) * sizeof(char));

  //初始化俄罗斯方块方阵（电脑）
  memset(pstParam->TetrisPlaySpaceCOM, 0,
	  sizeof(pstParam->TetrisPlaySpaceCOM) * sizeof(char));

  //初始化俄罗斯方块方阵（自定义方块模式）
  memset(pstParam->TetrisCustomizeBlocksSpace, 0,
    sizeof(pstParam->TetrisCustomizeBlocksSpace) * sizeof(char));

  //初始化方块链表
  pstParam->pstCustomizedBlockNodes = NULL;

  //临时debug:
  //pstParam->pstCustomizedBlockNodes = NULL;

  //方块总数
  pstParam->nBlockNum = 0;

  //初始化快捷数组
  for (i = 0; i < MAX_BLOCK_NUM; i++)
  {
    pstParam->pstFastArray[i] = NULL;
  }

  //初始化BlockElement链表
  pstParam->pstFirstBlockElementPlayer = NULL;

  //初始化BlockElement链表
  pstParam->pstFirstBlockElementCOM = NULL;

  //初始化电脑速度表
  memcpy(pstParam->nCOMSpeedList, nCOMSpeed,
    _countof(pstParam->nCOMSpeedList) * sizeof(int));    

  //初始化电脑难度等级
  pstParam->nCOMLevel = 5;
  //默认电脑不会立即下落功能
  pstParam->isStraightDown = false;

  /*//AIdebug
  pstParam->CurrentPointerToBlockList = 0;

  for (int m = 0; m < 100; m++)
  {
    pstParam->BlockList[m] = 3;
  }*/

  return 0;
}

//初始化环境
static int initialize_environment()
{
  //设定程序标题
  change_program_title__interface();

  //隐藏光标
  hide_cursor__interface();

  return 0;
}