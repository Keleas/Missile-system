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


RLS::RLS(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(recieve_pbu_msg);
    declareteQueue(recieve_target_msg);
}

bool RLS::init(const rapidjson::Value& initial_data)
{
    double Loc_tmp[3];
    Loc_tmp[0] = initial_data["Loc"][0].GetDouble();
    Loc_tmp[1] = initial_data["Loc"][1].GetDouble();
    Loc_tmp[2] = initial_data["Loc"][2].GetDouble();

    double n[3];
    n[0] = initial_data["n"][0].GetDouble();
    n[1] = initial_data["n"][1].GetDouble();
    n[2] = initial_data["n"][2].GetDouble();

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
    //write_to_csv();
}

void RLS::step(double time)
{
    TG = argInit_struct0_T();

    if (!recieve_target_msg.empty())
    {
        // Initialize function input argument 'TG'.
        

        /*Trajectory traj_msg;
        traj_msg.target_coords = recieve_target_msg.front().message.coord;
        traj_msg.target_v = recieve_target_msg.front().message.vels;
        traj_msg.sigma = { 7.0, 8.0, 9.0 };
        traj_msg.sigma_half_axis = { 10.0, 11.0, 12.0 };
        traj_msg.target_id = recieve_target_msg.front().source_id;
        
        recieve_target_msg.pop_front();

        //find target
        calculate(time);        

        send<Trajectory>(time, traj_msg);*/
    }


    emxInit_struct2_T(&MSG);

    MFR_V2_Cycle(TG, &MFR, 0.1, &MSG);

    /*TargetCoords target_msg;
    target_msg.target_coords = { 1.0, 2.0, 3.0 };
    target_msg.target_v = { 4.0, 5.0, 6.0 };
    target_msg.zur_coords = { -7.0, -8.0, -9.0 };
    target_msg.zur_v = { -10.0, -11.0, -12.0 };

    send<TargetCoords>(time, target_msg);*/

    //write_to_csv();
}

void RLS::calculate(double time)
{
    // update all
}

void RLS::endStep()
{
    MFR_V2_Cycle_terminate();
    //write_to_csv();
}