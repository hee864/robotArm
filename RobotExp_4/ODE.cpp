#include "stdafx.h"
#include "ODE.h"
#include "SystemMemory.h"
#include "DataType.h"

#ifndef DRAWSTUFF_TEXTURE_PATH
#define DRAWSTUFF_TEXTURE_PATH "./../ode-0.13/drawstuff/textures"
#endif

#define GRAVITY 9.81
#define MAX_JOINT_NUM 2

#define DEG2RAD 0.0174533
#define RAD2DEG 57.2958


//ODE Global Variable
dsFunctions g_Fn;

static dWorldID g_World;
static dSpaceID g_Space;
static dJointGroupID g_Contactgroup;
static dGeomID g_Ground;

//My Robot Global Variable
Object g_oObj[MAX_JOINT_NUM + 1];
static dJointID g_oJoint[MAX_JOINT_NUM + 1];

double g_tar_q[MAX_JOINT_NUM] = { 0.0, 0.0 };
double g_cur_q[MAX_JOINT_NUM] = { 0.0, 0.0 };

void InitDrawStuff() {

    g_Fn.version = DS_VERSION;
    g_Fn.start = &StartDrawStuff;
    g_Fn.step = &SimLoopDrawStuff;
    g_Fn.command = &CommandDrawStuff;
    g_Fn.stop = StopDrawStuff;
    g_Fn.path_to_textures = DRAWSTUFF_TEXTURE_PATH;
}


void InitODE() {

    //TO DO
    //setDrawStuff();
    dInitODE();
    g_World = dWorldCreate();
    g_Space = dHashSpaceCreate(0);
    g_Contactgroup = dJointGroupCreate(0);
    g_Ground = dCreatePlane(g_Space, 0, 0, 1, 0);
    dWorldSetGravity(g_World, 0, 0, -9.8);
    dWorldSetERP(g_World, 1.0);
    dWorldSetCFM(g_World, 1e-5);
}



void RunODE(size_t width, size_t height) {

    //TO DO
    InitDrawStuff();
    InitODE();

    InitRobot();

    //run simulation
    dsSimulationLoop(0, 0, width, height, &g_Fn);
}



void ReleaseODE() {

    dJointGroupDestroy(g_Contactgroup);
    dSpaceDestroy(g_Space);
    dWorldDestroy(g_World);
    dCloseODE();
}



void StartDrawStuff() {

    //TO DO
    // ī�޶� �� ����
    float dPos[3] = { 3.0,3.0,5.0 };   // X, Y, Z ��ǥ
    float dRot[3] = { -135.0,-45.0,0.0 };   // X�� Y�� Z�� ���� ȸ��
    dsSetViewpoint(dPos, dRot);
}


void SimLoopDrawStuff(int pause)
{

    //TO DO
    DataType_t jointData;
    GET_SYSTEM_MEMORY("JointData", jointData);

    g_tar_q[0] = jointData.Q_tar[0];
    g_tar_q[1] = jointData.Q_tar[1];

    jointData.Q_cur[0] = g_cur_q[0];
    jointData.Q_cur[1] = g_cur_q[1];

    SET_SYSTEM_MEMORY("JointData", jointData);

    if (g_tar_q[0] >= 360.0 * DEG2RAD) g_tar_q[0] -= 360.0 * DEG2RAD;
    if (g_tar_q[0] <= -360.0 * DEG2RAD) g_tar_q[0] += 360.0 * DEG2RAD;
    // 
    // 
    //Robot Control
    PControl();

    //Close Loop Setting
    double dt = 0.01; //��ǰ� ���������� ���귮�� ������, dt��ŭ �ڵ带 �ѽ��� ������
    dWorldStep(g_World, dt);

    //Draw Robot
    dsSetColor(1., 0., 0.);
    dsDrawCapsuleD(dBodyGetPosition(g_oObj[0].body), dBodyGetRotation(g_oObj[0].body), 0.5, 0.125);
    dsSetColor(0., 1., 0.);
    dsDrawCapsuleD(dBodyGetPosition(g_oObj[1].body), dBodyGetRotation(g_oObj[1].body), 1.0, 0.125);
    dsSetColor(0., 0., 1.);
    dsDrawCapsuleD(dBodyGetPosition(g_oObj[2].body), dBodyGetRotation(g_oObj[2].body), 0.5, 0.125);
}


void CommandDrawStuff(int cmd) {

    //TO DO

}



void StopDrawStuff() {

    //TO DO

}


void InitRobot()
{
    //TO DO
    //Body ����
    dMass mass;
    dMatrix3 R;

    //�����߽���
    dReal x[MAX_JOINT_NUM + 1] = { 0.00, 0.00, 0.00 };
    dReal y[MAX_JOINT_NUM + 1] = { 0.0, 0.0, 0.0 };
    dReal z[MAX_JOINT_NUM + 1] = { 0.25, 1.00, 1.75 };

    //��ũ �ڼ�
    dReal ori_x[MAX_JOINT_NUM + 1] = { 0.0, 0.0, 0.0 };
    dReal ori_y[MAX_JOINT_NUM + 1] = { 0.0, 0.0, 0.0 };
    dReal ori_z[MAX_JOINT_NUM + 1] = { 1.0, 1.0, 1.0 };
    dReal ori_q[MAX_JOINT_NUM + 1] = { 0.0, 0.0, 0.0 };

    //�� �ѵ��� ��ũ ����
    dReal length[MAX_JOINT_NUM + 1] = { 0.5, 1.0, 0.5 };

    //�ѵ��� ����
    dReal weight[MAX_JOINT_NUM + 1] = { 1.0,1.0, 1.0 };

    //ĸ���� ������
    dReal r[MAX_JOINT_NUM + 1];
    for (int i = 0; i < MAX_JOINT_NUM + 1; i++)
        r[i] = 0.125;

    //Body ����
    for (int i = 0; i < MAX_JOINT_NUM + 1; i++)
    {
        g_oObj[i].body = dBodyCreate(g_World);
        dBodySetPosition(g_oObj[i].body, x[i], y[i], z[i]);
        dMassSetZero(&mass);
        dMassSetCapsuleTotal(&mass, weight[i], 1, r[i], length[i]);
        dBodySetMass(g_oObj[i].body, &mass);
        g_oObj[i].geom = dCreateCapsule(g_Space, r[i], length[i]);
        dGeomSetBody(g_oObj[i].geom, g_oObj[i].body);
        dRFromAxisAndAngle(R, ori_x[i], ori_y[i], ori_z[i], ori_q[i]);
        dBodySetRotation(g_oObj[i].body, R);
    }

    ///////////////////////////////////////////////////////////
    //�� ����Ʈ�� ȸ������ ��ġ
    dReal c_x[MAX_JOINT_NUM + 1] = { 0.0, 0.0, 0.0 };
    dReal c_y[MAX_JOINT_NUM + 1] = { 0.0, 0.0, 0.0 };
    dReal c_z[MAX_JOINT_NUM + 1] = { 0.0, 0.5, 1.5 };

    //ȸ������ �����̼� ����
    dReal axis_x[MAX_JOINT_NUM + 1] = { 0.0, 0.0, 0.0 };
    dReal axis_y[MAX_JOINT_NUM + 1] = { 0.0, 1.0, 1.0 };
    dReal axis_z[MAX_JOINT_NUM + 1] = { 1.0, 0.0, 0.0 };

    //���� �� ����
    g_oJoint[0] = dJointCreateFixed(g_World, 0);
    dJointAttach(g_oJoint[0], 0, g_oObj[0].body);
    dJointSetFixed(g_oJoint[0]);
    //����Ʈ ����
    for (int i = 1; i < MAX_JOINT_NUM + 1; i++)
    {
        g_oJoint[i] = dJointCreateHinge(g_World, 0);
        dJointAttach(g_oJoint[i], g_oObj[i].body, g_oObj[i - 1].body);
        dJointSetHingeAnchor(g_oJoint[i], c_x[i], c_y[i], c_z[i]);
        dJointSetHingeAxis(g_oJoint[i], axis_x[i], axis_y[i], axis_z[i]);
    }
}

void PControl()
{

    //TO DO
    dReal dKp = 10.0, dMax = 100.0;
    dReal dError_Q[MAX_JOINT_NUM];

    for (int i = 1; i < MAX_JOINT_NUM + 1; i++)
    {
        g_cur_q[i - 1] = dJointGetHingeAngle(g_oJoint[i]);
        if (g_tar_q[i - 1] - g_cur_q[i - 1] > 180.0 * DEG2RAD)
        {
            g_cur_q[i - 1] += 359.9 * DEG2RAD;
        }

        if (g_tar_q[i - 1] - g_cur_q[i - 1] < -180.0 * DEG2RAD)
        {
            g_cur_q[i - 1] -= 359.9 * DEG2RAD;
        }

        dError_Q[i - 1] = g_tar_q[i - 1] - g_cur_q[i - 1];
        dJointSetHingeParam(g_oJoint[i], dParamVel, dKp * dError_Q[i - 1]);
        dJointSetHingeParam(g_oJoint[i], dParamFMax, dMax);
    }
}