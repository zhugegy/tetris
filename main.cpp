// ��Ŀ����˹����.cpp : �������̨Ӧ�ó������ڵ㡣
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

static int initialize_parameter(Param *pstParam);
static int initialize_environment();

int _tmain(int argc, _TCHAR* argv[])
{
  Param stMainParam;    //��Ҫ�����ṹ��

  //��ʼ������
  initialize_parameter(&stMainParam);

  //��ʼ�����滷��
  initialize_environment();

  //������ѭ��
  while (stMainParam.eStageFlag != STAGE_QUIT)
  {
    //�ı������
    change_interface_style__interface(stMainParam.eStageFlag);

    switch (stMainParam.eStageFlag)
    {
    case STAGE_MAIN_MENU:
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
  
  //��ʼ���������
  srand((unsigned) time(NULL)); //��ʱ�����֣�ÿ�β����������һ��

  //��ʼ����̨
  //pstParam->eStageFlag = stage_main_menu;
  //debug
  //pstParam->eStageFlag = STAGE_PLAY_SOLO;
  //pstParam->eStageFlag = STAGE_CUSTOMIZE_BLOCKS;
  pstParam->eStageFlag = STAGE_PLAY_VS_COM;


  //��ʼ������˹���鷽����ң�
  memset(pstParam->TetrisPlaySpacePlayer, 0, 
    sizeof(pstParam->TetrisPlaySpacePlayer) * sizeof(char));

  //��ʼ������˹���鷽�󣨵��ԣ�
  memset(pstParam->TetrisPlaySpaceCOM, 0,
	  sizeof(pstParam->TetrisPlaySpaceCOM) * sizeof(char));

  //��ʼ������˹���鷽���Զ��巽��ģʽ��
  memset(pstParam->TetrisCustomizeBlocksSpace, 0,
    sizeof(pstParam->TetrisCustomizeBlocksSpace) * sizeof(char));

  //���ļ����뷽������
  pstParam->pstCustomizedBlockNodes = NULL;
  load_block_list__file_operator(pstParam);

  //��ʱdebug:
  //pstParam->pstCustomizedBlockNodes = NULL;

  //�ѷ��������洢
  pstParam->nBlockNum = get_block_total_num__chain_list_processor(pstParam);

  //��ʼ���������
  for (i = 0; i < MAX_BLOCK_NUM; i++)
  {
    pstParam->pstFastArray[i] = NULL;
  }

  //������������������
  build_fast_array__chain_list_processor(pstParam);

  //Ԥ�������з��飨�ѷ���ĳ���λ�����°��źã����м���ã�
  pre_process_blocks__data_processor(pstParam);

  //��ʼ��BlockElement����
  pstParam->pstFirstBlockElementPlayer = NULL;

  //��ʼ��BlockElement����
  pstParam->pstFirstBlockElementCOM = NULL;

  return 0;
}

//��ʼ������
static int initialize_environment()
{
  //�趨�������
  change_program_title__interface();

  //���ع��
  hide_cursor__interface();

  return 0;
}