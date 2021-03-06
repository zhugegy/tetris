#include "stdafx.h"
#include "play_solo.h"

#include "data_processor.h"
#include "interface.h"
#include "main_loop.h"

int play_solo(Param *pstParam)
{
  //把俄罗斯方块方阵置为开始状态
  set_tetris_space_to_start__data_processor(pstParam->TetrisPlaySpacePlayer);

  //载入方块信息
  reload_block_info(pstParam);

  //打印背景
  print_tetris_play_ground__interface(pstParam->TetrisPlaySpacePlayer, 
    INTERFACE_PLAY_SOLO_ANCHOR_POINT_TETRIS_SPACE_X * 2, 
    INTERFACE_PLAY_SOLO_ANCHOR_POINT_TETRIS_SPACE_Y);

  //进入程序循环
  tetris_loop__main_loop(pstParam);
  

  return 0;
}