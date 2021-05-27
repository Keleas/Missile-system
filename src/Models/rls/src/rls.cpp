#include <map>
#include "rls.h"
#include "MFR_V2_Cycle_terminate.cpp"
#include "MFR_V2_Cycle.cpp"

static void argInit_1x3_real_T(double result[3])
{
    double result_tmp_tmp;

    // Loop over the array to initialize each element.
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_tmp_tmp = 0;
    result[0] = result_tmp_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[1] = result_tmp_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[2] = result_tmp_tmp;
}

//
// Arguments    : double result[9]
// Return Type  : void
//
static void argInit_3x3_real_T(double result[9])
{
    int idx0;
    double result_tmp_tmp;

    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < 3; idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result_tmp_tmp = 0;
        result[idx0] = result_tmp_tmp;

        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result[idx0 + 3] = result_tmp_tmp;

        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result[idx0 + 6] = result_tmp_tmp;
    }
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T* argInit_Unboundedx1_real_T()
{
    emxArray_real_T* result;
    static const int iv[1] = { 2 };

    int idx0;

    // Set the size of the array.
    // Change this size to the value that the application requires.
    result = emxCreateND_real_T(1, iv);

    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result->data[idx0] = 0;
    }

    return result;
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T* argInit_Unboundedx3_real_T()
{
    emxArray_real_T* result;
    int idx0;
    double result_tmp_tmp;

    // Set the size of the array.
    // Change this size to the value that the application requires.
    result = emxCreate_real_T(2, 3);

    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result_tmp_tmp = 0;
        result->data[idx0] = result_tmp_tmp;

        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result->data[idx0 + result->size[0]] = result_tmp_tmp;

        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result->data[idx0 + result->size[0] * 2] = result_tmp_tmp;
    }

    return result;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
    return 0.0;
}

//
// Arguments    : void
// Return Type  : struct0_T
//
static struct0_T argInit_struct0_T()
{
    struct0_T result;

    // Set the value of each structure field.
    // Change this value to the value that the application requires.
    result.ID = argInit_Unboundedx1_real_T();
    result.R0 = argInit_Unboundedx3_real_T();
    result.V = argInit_Unboundedx3_real_T();
    result.RCS = argInit_Unboundedx1_real_T();
    return result;
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T* c_argInit_UnboundedxUnbounded_r()
{
    emxArray_real_T* result;
    int idx0;
    int idx1;

    // Set the size of the array.
    // Change this size to the value that the application requires.
    result = emxCreate_real_T(2, 2);

    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
            // Set the value of the array element.
            // Change this value to the value that the application requires.
            result->data[idx0 + result->size[0] * idx1] = argInit_real_T();
        }
    }

    return result;
}

void MFR_v2_Agent(double n, emxArray_real_T* RES, std::vector<double> target_vec)
{
    int loop_ub;
    int i;
    loop_ub = static_cast<int>(n);
    i = RES->size[0];
    RES->size[0] = loop_ub;
    emxEnsureCapacity_real_T(RES, i);
    for (i = 0; i < loop_ub; i++) {
        RES->data[i] = target_vec.at(i);
    }
}


static void main_MFR_V2_GenerateTrajectoryType(struct0_T TG, 
    std::vector<double> target_id_vec, std::vector<double> target_coord0_vec,
    std::vector<double> target_coord1_vec, std::vector<double> target_coord2_vec,
    std::vector<double> target_v0_vec, std::vector<double> target_v1_vec,
    std::vector<double> target_v2_vec, std::vector<double> target_name_vec)
{
    
    emxArray_real_T* TG_ID;
    emxArray_real_T* TG_R0X;
    emxArray_real_T* TG_R0Y;
    emxArray_real_T* TG_R0Z;
    emxArray_real_T* TG_VX;
    emxArray_real_T* TG_VY;
    emxArray_real_T* TG_VZ;
    emxArray_real_T* TG_Type;

    // Initialize function 'MFR_V2_GenerateTrajectoryType' input arguments.
    // Initialize function input argument 'TG_ID'.
    TG_ID = argInit_Unboundedx1_real_T();
    MFR_v2_Agent(target_id_vec.size(), TG_ID, target_id_vec);

    // Initialize function input argument 'TG_R0X'.
    TG_R0X = argInit_Unboundedx1_real_T();
    MFR_v2_Agent(target_coord0_vec.size(), TG_R0X, target_coord0_vec);

    // Initialize function input argument 'TG_R0Y'.
    TG_R0Y = argInit_Unboundedx1_real_T();
    MFR_v2_Agent(target_coord1_vec.size(), TG_R0Y, target_coord1_vec);

    // Initialize function input argument 'TG_R0Z'.
    TG_R0Z = argInit_Unboundedx1_real_T();
    MFR_v2_Agent(target_coord2_vec.size(), TG_R0Z, target_coord2_vec);

    // Initialize function input argument 'TG_VX'.
    TG_VX = argInit_Unboundedx1_real_T();
    MFR_v2_Agent(target_v0_vec.size(), TG_VX, target_v0_vec);

    // Initialize function input argument 'TG_VY'.
    TG_VY = argInit_Unboundedx1_real_T();
    MFR_v2_Agent(target_v1_vec.size(), TG_VY, target_v1_vec);

    // Initialize function input argument 'TG_VZ'.
    TG_VZ = argInit_Unboundedx1_real_T();
    MFR_v2_Agent(target_v2_vec.size(), TG_VZ, target_v2_vec);

    // Initialize function input argument 'TG_Type'.
    TG_Type = argInit_Unboundedx1_real_T();
    MFR_v2_Agent(target_name_vec.size(), TG_Type, target_id_vec);

    // Call the entry-point 'MFR_V2_GenerateTrajectoryType'.
    MFR_V2_GenerateTrajectoryType(TG_ID, TG_R0X, TG_R0Y, TG_R0Z, TG_VX, TG_VY,
        TG_VZ, TG_Type, &TG);
}


RLS::RLS(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    RLS::id = id;
    //declareteQueue(recieve_pbu_msg);
    declareteQueue(recieve_target_msg);
}

bool RLS::init(const rapidjson::Value& initial_data)
{
    targets_RCS.insert(std::make_pair("F-35", 0));
    targets_RCS.insert(std::make_pair("Миг-29", 1));
    targets_RCS.insert(std::make_pair("J-31", 2));
    targets_RCS.insert(std::make_pair("Anti-aircraft", 3));

    double Loc_tmp[3];
    Loc_tmp[0] = initial_data["x"].GetDouble();
    Loc_tmp[1] = initial_data["y"].GetDouble();
    Loc_tmp[2] = initial_data["z"].GetDouble();

    double n[3];
    n[0] = initial_data["rotate_x"].GetDouble();
    n[1] = initial_data["rotate_y"].GetDouble();
    n[2] = initial_data["rotate_z"].GetDouble();

    emxInit_struct1_T(&MFR);

    MFR_V2_GenerateMFRType(Loc_tmp, n, initial_data["lambda"].GetDouble(), 
        initial_data["Dmax"].GetDouble(), initial_data["Dmin"].GetDouble(),
        initial_data["Tscan"].GetDouble(), initial_data["Timp"].GetDouble(),
        initial_data["V_res"].GetDouble(), initial_data["asim_res"].GetDouble(),
        initial_data["elev_res"].GetDouble(), initial_data["asim_res_trace_cf"].GetDouble(),
        initial_data["elev_res_trace_cf"].GetDouble(),
        initial_data["elev1"].GetDouble(),
        initial_data["elev2"].GetDouble(), 
        initial_data["Nasim"].GetDouble(),
        initial_data["Nelev"].GetDouble(),
        initial_data["Bandwidth"].GetDouble(),
        initial_data["Noise"].GetDouble(),
        initial_data["Gain"].GetDouble(),
        initial_data["P_peak"].GetDouble(),
        initial_data["Tr"].GetDouble(), 
        initial_data["Ntraj"].GetDouble(), 
        initial_data["Nmissiles"].GetDouble(),
        &MFR);


    //std::cout << "target_id: " << std::endl;
    return true;
}

void RLS::firstStep()
{
    setLogHeader("RLS_type", "id", "X", "Y", "Z", "target_X", "target_Y", "target_Z", "target_Vx", "target_Vy", "target_Vz", "time_detect", "target_id", "target_type");
}

void printMSG(id_type id, double time, TargetMsg msg)
{
    std::cout << "Message from " << id << " at time " << time << std::endl;
    std::cout << "coord: " << msg.coord[0] << " " << msg.coord[1] << " " << msg.coord[2] << std::endl;
    std::cout << "vel: " << msg.vels[0] << " " << msg.vels[1] << " " << msg.vels[2] << std::endl;
    std::cout << "name: " << msg.name << std::endl;
}

void RLS::step(double time)
{
    RLS::time = time;
    TargetMsg msg;
    msg.coord = { 15000, 10000, 3000 };
    msg.vels = { 7, 8, 9 };
    msg.type_model = "F-35";

    send<TargetMsg>(1, msg);

    TG = argInit_struct0_T();

    std::vector<double> target_id_vec;
    std::vector<double> target_coord0_vec;
    std::vector<double> target_coord1_vec;
    std::vector<double> target_coord2_vec;
    std::vector<double> target_v0_vec;
    std::vector<double> target_v1_vec;
    std::vector<double> target_v2_vec;
    std::vector<double> target_name_vec;

    while (!recieve_target_msg.empty())
    {
        
        TargetMsg msg = recieve_target_msg.front().message;

        target_id_vec.push_back(recieve_target_msg.front().source_id);
        target_coord0_vec.push_back(msg.coord[0]);
        target_coord1_vec.push_back(msg.coord[1]);
        target_coord2_vec.push_back(msg.coord[2]);
        target_v0_vec.push_back(msg.vels[0]);
        target_v1_vec.push_back(msg.vels[1]);
        target_v2_vec.push_back(msg.vels[2]);
        
        target_name_vec.push_back(targets_RCS[msg.type_model]);

        //printMSG(recieve_target_msg.front().source_id, recieve_target_msg.front().time, msg);

        recieve_target_msg.pop_front();
    }

    main_MFR_V2_GenerateTrajectoryType(TG, target_id_vec, target_coord0_vec,
        target_coord1_vec, target_coord2_vec, target_v0_vec, target_v1_vec, 
        target_v2_vec, target_name_vec);

    emxInit_struct2_T(&MSG);

    MFR_V2_Cycle(TG, &MFR, 1, &MSG);

    //std::cout << "name: " << (MSG.IDTracked->size[0]) << std::endl;

    for (int i = 0; i < (int) (MSG.IDTracked->size[0]); i++)
    {
        RLCMsg target_msg;
        target_msg.target_id = MSG.IDTracked->data[i];
        target_msg.coordinates = { MSG.RTrackedX->data[i], 
                                    MSG.RTrackedY->data[i],
                                    MSG.RTrackedZ->data[i] };
        target_msg.speed = { MSG.VTrackedX->data[i],
                                MSG.VTrackedY->data[i],
                                MSG.VTrackedZ->data[i] };
        target_msg.time = time;

        send<RLCMsg>(time, target_msg);

        writeLog(time, RLS::id, RLS::id, MFR.Loc[0], MFR.Loc[1], MFR.Loc[2], 
                MSG.RTrackedX->data[i], MSG.RTrackedY->data[i], MSG.RTrackedZ->data[i], 
                MSG.VTrackedX->data[i], MSG.VTrackedY->data[i], MSG.VTrackedZ->data[i], time, MSG.IDTracked->data[i], MSG.IDTracked->data[i]);
    }

    emxDestroy_struct2_T(MSG);
    emxDestroy_struct0_T(TG);

    //write_to_csv();
}

void RLS::endStep()
{
    MFR_V2_Cycle_terminate();
    //write_to_csv();
}