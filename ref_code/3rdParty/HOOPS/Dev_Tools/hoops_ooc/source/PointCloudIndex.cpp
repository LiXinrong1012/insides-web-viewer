/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: PointCloudIndex.cpp,v 1.36 2010-10-19 22:05:02 chad Exp $
 */



#define HMUTEX_IMPLEMENT_MUTEX_FUNCTIONS
#include "hmutex.h"

#include "PointCloudIndex.h"

#include "PointCloudCommon.h"
#include "PointCloudMasterNode.h"
#include "PointCloudNodeRandomized.h"
#include "PointCloudStreamFileToolkit.h"
#include "StreamFilePointContainer.h"

#include <string.h>

/*****************************************************************************************************/
// static member initialization
bool TK_Point_Cloud_Index_Open_Segment::m_has_defined_callback = false;

float PointCloudIndexNodeData::m_uniform_rand[1024] = {
	0.513870f, 0.175741f, 0.308652f, 0.534534f,
	0.947628f, 0.171736f, 0.702231f, 0.226431f,
	0.494773f, 0.124720f, 0.083899f, 0.389647f,
	0.277226f, 0.368071f, 0.983437f, 0.535398f,
	0.765682f, 0.646473f, 0.767139f, 0.780237f,
	0.822951f, 0.151932f, 0.625477f, 0.314685f,
	0.346901f, 0.917204f, 0.519760f, 0.401154f,
	0.606758f, 0.785402f, 0.931523f, 0.869921f,
	0.866525f, 0.674520f, 0.758400f, 0.581893f,
	0.389248f, 0.355635f, 0.200232f, 0.826927f,
	0.415903f, 0.463522f, 0.979163f, 0.126436f,
	0.212637f, 0.958451f, 0.737463f, 0.409056f,
	0.780113f, 0.757899f, 0.956842f, 0.028096f,
	0.318728f, 0.756934f, 0.242995f, 0.589542f,
	0.043424f, 0.956025f, 0.319133f, 0.059360f,
	0.441876f, 0.915020f, 0.572247f, 0.118838f,
	0.569771f, 0.252048f, 0.495858f, 0.236734f,
	0.476961f, 0.406093f, 0.872998f, 0.426963f,
	0.358218f, 0.381988f, 0.043180f, 0.160587f,
	0.522351f, 0.696581f, 0.097100f, 0.400847f,
	0.773432f, 0.244827f, 0.342824f, 0.229994f,
	0.297877f, 0.304546f, 0.887207f, 0.036669f,
	0.651147f, 0.398606f, 0.676297f, 0.732578f,
	0.937797f, 0.233280f, 0.838481f, 0.967210f,
	0.778638f, 0.431518f, 0.674102f, 0.809358f,
	0.158765f, 0.279899f, 0.135323f, 0.864187f,
	0.750185f, 0.207999f, 0.139963f, 0.294589f,
	0.802805f, 0.218934f, 0.563082f, 0.715602f,
	0.197542f, 0.989825f, 0.250038f, 0.430608f,
	0.755274f, 0.860929f, 0.894781f, 0.978088f,
	0.395412f, 0.432205f, 0.127140f, 0.457675f,
	0.237831f, 0.986032f, 0.652831f, 0.604246f,
	0.241906f, 0.454873f, 0.789960f, 0.078819f,
	0.476410f, 0.152588f, 0.245752f, 0.944993f,
	0.614020f, 0.988186f, 0.477276f, 0.799684f,
	0.744184f, 0.380735f, 0.479891f, 0.526908f,
	0.098099f, 0.594211f, 0.347183f, 0.143366f,
	0.779540f, 0.710997f, 0.446139f, 0.704569f,
	0.095309f, 0.962825f, 0.551302f, 0.740264f,
	0.579039f, 0.637876f, 0.781656f, 0.187904f,
	0.302103f, 0.282807f, 0.684006f, 0.292919f,
	0.565391f, 0.418449f, 0.306581f, 0.444530f,
	0.565690f, 0.487929f, 0.606633f, 0.415860f,
	0.130424f, 0.255960f, 0.035758f, 0.977097f,
	0.114506f, 0.378054f, 0.646711f, 0.350446f,
	0.553049f, 0.358411f, 0.565451f, 0.475635f,
	0.163682f, 0.615225f, 0.172170f, 0.554712f,
	0.292231f, 0.872162f, 0.835062f, 0.844895f,
	0.895509f, 0.594763f, 0.540566f, 0.168211f,
	0.654958f, 0.690519f, 0.263855f, 0.106692f,
	0.814912f, 0.191361f, 0.423297f, 0.351858f,
	0.839209f, 0.137331f, 0.262667f, 0.177253f,
	0.479918f, 0.380171f, 0.504823f, 0.502776f,
	0.351924f, 0.525583f, 0.120635f, 0.519556f,
	0.607121f, 0.732908f, 0.556884f, 0.344134f,
	0.801968f, 0.590988f, 0.266907f, 0.670676f,
	0.552153f, 0.788935f, 0.887718f, 0.889998f,
	0.068109f, 0.800584f, 0.907367f, 0.644128f,
	0.165154f, 0.301360f, 0.166283f, 0.285169f,
	0.841976f, 0.536325f, 0.036350f, 0.207211f,
	0.021239f, 0.358133f, 0.621471f, 0.520032f,
	0.546037f, 0.153675f, 0.823362f, 0.033355f,
	0.025968f, 0.378132f, 0.616332f, 0.020394f,
	0.626561f, 0.915205f, 0.374798f, 0.729457f,
	0.395814f, 0.982265f, 0.597287f, 0.112332f,
	0.221591f, 0.799181f, 0.870664f, 0.738232f,
	0.013631f, 0.739560f, 0.418353f, 0.362033f,
	0.203911f, 0.183165f, 0.076289f, 0.115555f,
	0.159123f, 0.788256f, 0.040355f, 0.790644f,
	0.599013f, 0.402600f, 0.229052f, 0.182802f,
	0.614316f, 0.331902f, 0.605152f, 0.964109f,
	0.378071f, 0.184412f, 0.300094f, 0.054197f,
	0.144022f, 0.010448f, 0.884850f, 0.958016f,
	0.625903f, 0.955599f, 0.631040f, 0.039153f,
	0.351310f, 0.146339f, 0.106021f, 0.197440f,
	0.083947f, 0.026826f, 0.945717f, 0.919618f,
	0.907975f, 0.865609f, 0.148927f, 0.171789f,
	0.068223f, 0.651019f, 0.736875f, 0.102420f,
	0.160007f, 0.093974f, 0.121734f, 0.024643f,
	0.762306f, 0.956959f, 0.027900f, 0.646604f,
	0.108057f, 0.427927f, 0.309732f, 0.018603f,
	0.885293f, 0.757873f, 0.509539f, 0.165785f,
	0.762909f, 0.880830f, 0.499552f, 0.875130f,
	0.734772f, 0.235033f, 0.051616f, 0.605485f,
	0.875949f, 0.504011f, 0.678388f, 0.989394f,
	0.604792f, 0.496345f, 0.589750f, 0.895479f,
	0.044631f, 0.882853f, 0.108217f, 0.520112f,
	0.578829f, 0.009945f, 0.387075f, 0.477138f,
	0.192946f, 0.507894f, 0.775009f, 0.354395f,
	0.697759f, 0.912791f, 0.670958f, 0.705776f,
	0.426894f, 0.020912f, 0.212958f, 0.947594f,
	0.502821f, 0.194261f, 0.644719f, 0.127989f,
	0.264949f, 0.336029f, 0.703689f, 0.038137f,
	0.953592f, 0.754740f, 0.874348f, 0.634001f,
	0.243531f, 0.635797f, 0.850488f, 0.237380f,
	0.720950f, 0.339220f, 0.050226f, 0.485009f,
	0.897470f, 0.242293f, 0.527509f, 0.494446f,
	0.855048f, 0.345890f, 0.123841f, 0.215523f,
	0.115482f, 0.363218f, 0.204003f, 0.436071f,
	0.828279f, 0.509733f, 0.819508f, 0.410715f,
	0.870630f, 0.712983f, 0.643532f, 0.581447f,
	0.953245f, 0.461115f, 0.521089f, 0.358758f,
	0.325798f, 0.008809f, 0.978186f, 0.432064f,
	0.175729f, 0.159383f, 0.533711f, 0.578173f,
	0.314158f, 0.341818f, 0.157807f, 0.436559f,
	0.242659f, 0.201458f, 0.720482f, 0.220171f,
	0.194639f, 0.423127f, 0.774202f, 0.830553f,
	0.245082f, 0.005425f, 0.514215f, 0.345996f,
	0.082395f, 0.704941f, 0.260366f, 0.351500f,
	0.536126f, 0.869134f, 0.304142f, 0.079271f,
	0.454275f, 0.376648f, 0.464701f, 0.828528f,
	0.023977f, 0.903785f, 0.197636f, 0.633342f,
	0.129290f, 0.235913f, 0.600229f, 0.647284f,
	0.839841f, 0.842531f, 0.156927f, 0.213617f,
	0.624083f, 0.434771f, 0.568817f, 0.089778f,
	0.380915f, 0.724062f, 0.510823f, 0.794917f,
	0.883400f, 0.100720f, 0.660395f, 0.549224f,
	0.728357f, 0.451207f, 0.841428f, 0.773812f,
	0.385553f, 0.832817f, 0.627170f, 0.619888f,
	0.440254f, 0.224525f, 0.245860f, 0.495973f,
	0.622894f, 0.072769f, 0.132851f, 0.061927f,
	0.719590f, 0.850896f, 0.972971f, 0.658508f,
	0.957281f, 0.351030f, 0.576863f, 0.641238f,
	0.957214f, 0.927117f, 0.435064f, 0.587311f,
	0.850548f, 0.407890f, 0.293568f, 0.844298f,
	0.649812f, 0.898498f, 0.594616f, 0.389402f,
	0.469974f, 0.189573f, 0.126483f, 0.468008f,
	0.692872f, 0.992452f, 0.725989f, 0.980276f,
	0.668749f, 0.719332f, 0.377500f, 0.084539f,
	0.048655f, 0.027090f, 0.552158f, 0.986240f,
	0.341448f, 0.843535f, 0.131103f, 0.381173f,
	0.789165f, 0.094816f, 0.756421f, 0.521762f,
	0.154494f, 0.852768f, 0.953587f, 0.375148f,
	0.514112f, 0.120919f, 0.869126f, 0.841813f,
	0.651629f, 0.977923f, 0.967278f, 0.503504f,
	0.143889f, 0.297166f, 0.529382f, 0.869209f,
	0.734386f, 0.761293f, 0.299752f, 0.587922f,
	0.087534f, 0.390402f, 0.121784f, 0.596959f,
	0.517552f, 0.302667f, 0.908050f, 0.674572f,
	0.785702f, 0.926133f, 0.788127f, 0.365605f,
	0.559641f, 0.380423f, 0.777903f, 0.748953f,
	0.628632f, 0.247130f, 0.814128f, 0.015565f,
	0.468361f, 0.447621f, 0.497944f, 0.325742f,
	0.249118f, 0.447017f, 0.391145f, 0.914483f,
	0.881083f, 0.503097f, 0.208932f, 0.913631f,
	0.190476f, 0.178867f, 0.752893f, 0.859563f,
	0.820310f, 0.837558f, 0.927969f, 0.355177f,
	0.949512f, 0.338793f, 0.687162f, 0.854923f,
	0.424145f, 0.654674f, 0.247717f, 0.041641f,
	0.394495f, 0.624545f, 0.422543f, 0.763932f,
	0.051762f, 0.567174f, 0.410619f, 0.002836f,
	0.558119f, 0.969104f, 0.890137f, 0.836554f,
	0.763870f, 0.967937f, 0.758118f, 0.871967f,
	0.805478f, 0.849272f, 0.360280f, 0.111697f,
	0.178189f, 0.276087f, 0.554873f, 0.725476f,
	0.377031f, 0.469270f, 0.454261f, 0.694551f,
	0.699910f, 0.058088f, 0.187981f, 0.797889f,
	0.306573f, 0.819326f, 0.531039f, 0.908933f,
	0.127172f, 0.023837f, 0.741193f, 0.071652f,
	0.714201f, 0.609277f, 0.448963f, 0.324634f,
	0.631526f, 0.897755f, 0.944135f, 0.741983f,
	0.474287f, 0.077156f, 0.702491f, 0.659759f,
	0.113404f, 0.164886f, 0.496526f, 0.556712f,
	0.258443f, 0.672788f, 0.933905f, 0.558072f,
	0.932590f, 0.691985f, 0.767395f, 0.031124f,
	0.953489f, 0.616385f, 0.820038f, 0.241341f,
	0.013685f, 0.223617f, 0.869303f, 0.537804f,
	0.454426f, 0.332136f, 0.333983f, 0.036680f,
	0.326580f, 0.753247f, 0.107560f, 0.271482f,
	0.832403f, 0.756805f, 0.381819f, 0.778893f,
	0.741924f, 0.769335f, 0.804441f, 0.088873f,
	0.877684f, 0.523324f, 0.814327f, 0.087820f,
	0.261588f, 0.376432f, 0.498412f, 0.223525f,
	0.017617f, 0.019383f, 0.813708f, 0.520677f,
	0.624141f, 0.291269f, 0.518339f, 0.875659f,
	0.609605f, 0.321029f, 0.655303f, 0.599401f,
	0.285312f, 0.713854f, 0.932718f, 0.677017f,
	0.609074f, 0.001256f, 0.844311f, 0.712998f,
	0.773465f, 0.073566f, 0.873883f, 0.030701f,
	0.612440f, 0.813600f, 0.627509f, 0.894880f,
	0.420061f, 0.650248f, 0.237231f, 0.326019f,
	0.275079f, 0.250734f, 0.879970f, 0.475212f,
	0.465133f, 0.070299f, 0.755440f, 0.028332f,
	0.104297f, 0.978057f, 0.366780f, 0.608258f,
	0.537751f, 0.677771f, 0.447686f, 0.643890f,
	0.627297f, 0.142297f, 0.379761f, 0.674719f,
	0.511493f, 0.780460f, 0.443864f, 0.559684f,
	0.934146f, 0.555093f, 0.749184f, 0.559085f,
	0.734911f, 0.771001f, 0.183804f, 0.758285f,
	0.595749f, 0.751598f, 0.230494f, 0.801968f,
	0.637002f, 0.122963f, 0.991493f, 0.407687f,
	0.956814f, 0.924070f, 0.266023f, 0.627457f,
	0.707676f, 0.261940f, 0.024290f, 0.326155f,
	0.803820f, 0.730463f, 0.121714f, 0.845454f,
	0.853225f, 0.311646f, 0.597148f, 0.322065f,
	0.407988f, 0.978025f, 0.398834f, 0.629019f,
	0.126793f, 0.715010f, 0.881833f, 0.408749f,
	0.943250f, 0.181889f, 0.920699f, 0.166717f,
	0.833840f, 0.730267f, 0.981137f, 0.894340f,
	0.279215f, 0.998666f, 0.994388f, 0.189960f,
	0.012616f, 0.802055f, 0.378106f, 0.346613f,
	0.149141f, 0.535043f, 0.047464f, 0.375347f,
	0.289629f, 0.807506f, 0.760250f, 0.432832f,
	0.692901f, 0.531373f, 0.639691f, 0.622016f,
	0.110111f, 0.177342f, 0.218768f, 0.634590f,
	0.374954f, 0.420268f, 0.849756f, 0.203980f,
	0.343489f, 0.891966f, 0.822762f, 0.837656f,
	0.277312f, 0.260196f, 0.036983f, 0.797473f,
	0.263851f, 0.352559f, 0.568460f, 0.796818f,
	0.767509f, 0.544074f, 0.978057f, 0.383297f,
	0.905421f, 0.127171f, 0.703433f, 0.475726f,
	0.541572f, 0.882860f, 0.378739f, 0.024161f,
	0.793020f, 0.571817f, 0.425810f, 0.261735f,
	0.041986f, 0.564147f, 0.760584f, 0.517028f,
	0.047540f, 0.326567f, 0.958506f, 0.055750f,
	0.250665f, 0.985759f, 0.722666f, 0.920458f,
	0.866411f, 0.686646f, 0.998429f, 0.237072f,
	0.856922f, 0.964343f, 0.578288f, 0.956949f,
	0.379068f, 0.848522f, 0.540710f, 0.503237f,
	0.800435f, 0.918961f, 0.366708f, 0.290287f,
	0.877425f, 0.031002f, 0.077912f, 0.584861f,
	0.189217f, 0.929689f, 0.239854f, 0.677883f,
	0.421336f, 0.471326f, 0.174257f, 0.835488f,
	0.592584f, 0.671205f, 0.224043f, 0.998121f,
	0.819073f, 0.296260f, 0.414839f, 0.696429f,
	0.709127f, 0.221386f, 0.356702f, 0.152700f,
	0.982787f, 0.268190f, 0.729845f, 0.036606f,
	0.409676f, 0.744901f, 0.198083f, 0.843978f,
	0.658978f, 0.406216f, 0.093774f, 0.367398f,
	0.155271f, 0.051806f, 0.717985f, 0.227317f,
	0.533969f, 0.482248f, 0.599654f, 0.932485f,
	0.790131f, 0.031133f, 0.557473f, 0.438424f,
	0.714369f, 0.392092f, 0.908265f, 0.672690f,
	0.709623f, 0.959491f, 0.665593f, 0.995697f,
	0.582543f, 0.401555f, 0.072352f, 0.065822f,
	0.403230f, 0.684655f, 0.311095f, 0.077569f,
	0.027085f, 0.267528f, 0.735846f, 0.841522f,
	0.372520f, 0.684159f, 0.469148f, 0.674850f,
	0.048279f, 0.234088f, 0.708087f, 0.571106f,
	0.424115f, 0.998893f, 0.583062f, 0.618073f,
	0.738576f, 0.903587f, 0.913034f, 0.132409f,
	0.337658f, 0.041696f, 0.701007f, 0.479835f,
	0.638056f, 0.982748f, 0.713494f, 0.049626f,
	0.908784f, 0.280946f, 0.987726f, 0.352143f,
	0.464900f, 0.903755f, 0.610331f, 0.708161f,
	0.367089f, 0.799161f, 0.611261f, 0.498755f,
	0.220860f, 0.320354f, 0.316693f, 0.444467f,
	0.169097f, 0.726585f, 0.004669f, 0.882529f,
	0.671724f, 0.478939f, 0.207223f, 0.510888f,
	0.166229f, 0.549786f, 0.502737f, 0.567762f,
	0.202790f, 0.464650f, 0.142286f, 0.915509f,
	0.147772f, 0.295251f, 0.353709f, 0.997533f,
	0.049327f, 0.322467f, 0.667180f, 0.136993f,
	0.758850f, 0.587974f, 0.105996f, 0.146053f,
	0.902052f, 0.053301f, 0.586361f, 0.714431f,
	0.793388f, 0.585058f, 0.369900f, 0.546001f
};

/*****************************************************************************************************/

PointCloudIndexNodeData::PointCloudIndexNodeData ( PointCloudWorld * pcw_in, float min_intensity_in, float max_intensity_in ) {
	m_pcw = pcw_in;
	m_index_file_name = new wchar_t [m_pcw->GetIndexFileNameSize() + 1];
	m_pcw->GetIndexFileName(m_index_file_name);
	m_index_tk = new PointCloudStreamFileToolkit(m_pcw);
	m_index_tk->SetOpcodeHandler(TKE_Open_Segment, new TK_Point_Cloud_Index_Open_Segment(m_pcw, this));
	m_index_tk->SetOpcodeHandler(TKE_Close_Segment, new TK_Point_Cloud_Index_Close_Segment(m_pcw, this));
	m_index_tk->SetBufferLimit(OOC_TOOLKIT_BUFFER_SIZE);
	m_node_tk = new PointCloudStreamFileToolkit(m_pcw);
	m_node_tk->SetOpcodeHandler(TKE_Shell, new TK_Point_Cloud_Node_Randomized(this));
	m_node_tk->SetBufferLimit(OOC_TOOLKIT_BUFFER_SIZE);
	m_node_shell_size = m_pcw->GetMaxShellSize();
	m_node_shell_cutoff = LOD_POINT_COUNT_CUTOFF;
	m_min_intensity = min_intensity_in;
	m_max_intensity = max_intensity_in;

	m_rand48_seed = 1941;

	m_nodes_processed = 0;
	m_num_files_written = 0;
	m_pcmn = 0;
}

PointCloudIndexNodeData::~PointCloudIndexNodeData () {
	if (m_index_file_name) {
		if (m_index_tk)
			m_index_tk->Finalize_Stream_File(m_index_file_name);
		else
			assert(0);
		delete [] m_index_file_name;
	}
	if (m_index_tk)
		delete m_index_tk;
	if (m_node_tk)
		delete m_node_tk;
	if (m_pcmn)
		delete m_pcmn;
}

float PointCloudIndexNodeData::unirand () {
	return m_uniform_rand[++m_rand48_seed & 0x3FF];
}

void PointCloudIndexNodeData::Update () alter {	
	SetBBox(m_node_metadata->GetBounds());
	m_segment_list.Append(m_traversal_state);

	if (GetIsEnteringNode()) {
		m_bbox_list.AppendArray(m_bbox, 6);
		m_lod_point_list_list.AddFirst(new PointList());

		uint64_t subtree_count = m_node_metadata->GetNumItemsInSubtree(),
			lbf_subtree_count = m_node_metadata->GetNumItemsInLeftBottomFrontSubtree(),
			rtb_subtree_count = m_node_metadata->GetNumItemsInRightTopBackSubtree(),
			overlap_subtree_count = m_node_metadata->GetNumItemsInOverlapSubtree();
		int parent_point_count = (int)(m_propagation_amount.Count() ? m_propagation_amount.PeekFirst() : 0);
		double lbf_percentage = (double)lbf_subtree_count / (double)subtree_count,
			   rtb_percentage = (double)rtb_subtree_count / (double)subtree_count,
			   overlap_percentage = (double)overlap_subtree_count / (double)subtree_count;
		uint64_t lbf_point_count = (uint64_t)(lbf_percentage * (m_node_shell_size + parent_point_count) + 0.5), 
			rtb_point_count = (uint64_t)(rtb_percentage * (m_node_shell_size + parent_point_count) + 0.5),
			overlap_point_count = (uint64_t)(overlap_percentage * (m_node_shell_size + parent_point_count) + 0.5);

		// we cast to int since for any reasonable node shell size, that should be more than sufficient
		if (overlap_subtree_count)
			m_propagation_amount.AddFirst((int)(overlap_point_count < overlap_subtree_count ? overlap_point_count : overlap_subtree_count));
		if (rtb_subtree_count)
			m_propagation_amount.AddFirst((int)(rtb_point_count < rtb_subtree_count ? rtb_point_count : rtb_subtree_count));
		if (lbf_subtree_count)
			m_propagation_amount.AddFirst((int)(lbf_point_count < lbf_subtree_count ? lbf_point_count : lbf_subtree_count));
			
		return;
	}
	
	// add a reference (if one exists) to existing segment/node and then close it
	assert(m_node_point_list.Count() == 0);
	
	bool need_to_randomize = false;
	
	if (m_container) {
		int container_point_list_count;
		PCPoint *container_point_list;
		m_container->GetPointList(container_point_list_count, container_point_list);
		m_node_point_list.AppendArray(container_point_list, container_point_list_count);
			
		need_to_randomize = true;
		m_container->DeletePointList();
	}
	
	PointList *lod_point_list = m_lod_point_list_list.RemoveFirst();
	
	if (lod_point_list->Count() > 0) {
		m_node_point_list.AppendArray(*lod_point_list, lod_point_list->Count());
		
		need_to_randomize = true;
	}
	
	if (need_to_randomize && m_pcw->GetRandomizePoints()) {
		PCPoint temp;
		int i, j;
		for ( i = m_node_point_list.Count() - 1 ; i >= 0 ; i-- ) {
			j = (int)(unirand() * i + 0.5f);

			if (i == j)
				continue;
			
			temp = m_node_point_list[i];
			m_node_point_list[i] = m_node_point_list[j];
			m_node_point_list[j] = temp;
		}
	}
	
	delete lod_point_list;
	
	if (m_lod_point_list_list.Count() > 0) {	
		int num_lod_points = m_propagation_amount.RemoveFirst();
		if (m_node_point_list.Count() - num_lod_points <= m_node_shell_cutoff) {
			m_lod_point_list_list.PeekFirst()->AppendArray(m_node_point_list, m_node_point_list.Count());
			m_node_point_list.SetCount(0);
		}
		else {
			for ( int i = 0 ; i < num_lod_points ; i++ ) {
				m_lod_point_list_list.PeekFirst()->Append(m_node_point_list.Pop());
			}
		}
	}
	
	if (m_node_point_list.Count() > 0) {
 		m_node_tk->Restart();
		m_node_buffer.SetCount(0);
		m_node_tk->Write_Stream_Buffer(&m_node_buffer);
	
		if (m_pcmn == 0)
			m_pcmn = new PointCloudMasterNode(m_pcw);

		unsigned int node_fid, node_offset, node_num_bytes;
		m_pcmn->ConcatenateNode(m_node_buffer, node_fid, node_offset, node_num_bytes);
		m_mnd_list.Append(node_fid);
		m_mnd_list.Append(node_offset);
		m_mnd_list.Append(node_num_bytes);

		m_node_point_list.SetCount(0);

		m_num_files_written++;
	}
	else {
		m_segment_list.Pop(); // remove close segment
		m_segment_list.Pop(); // remove open segment
		int old_bbox_list_length = m_bbox_list.Count();
		m_bbox_list.SetCount(old_bbox_list_length - 6);
	}

	if (++m_nodes_processed % 1000 == 0) {
		char temp[1024];
		char logging_str[4096] = { 0 };
		sprintf(temp, "%s K nodes / ", PrettifyInteger(m_nodes_processed / 1000));
		strcat(logging_str, temp);
		sprintf(temp, "%s files", PrettifyInteger(m_num_files_written));
		strcat(logging_str, temp);

		m_pcw->LogMessage(logging_str, true);
	}
}

void PointCloudIndexNodeData::ExportPointCloudIndex () alter {
	assert(m_num_files_written == m_segment_list.Count() / 2);
	H_FORMAT_TEXT logging_str = H_FORMAT_TEXT("Pruning resulted in %s node files.", PrettifyInteger(m_segment_list.Count() / 2));
	m_pcw->LogMessage(logging_str, true);

	int i, j, k;
	for ( i = 0, j = 0, k = 0 ; i < m_segment_list.Count() ; i++ ) {
		m_traversal_state = m_segment_list[i];
		if (GetIsEnteringNode()) {
			SetBBox(static_cast<float const *>(m_bbox_list) + j);
			j += 6;
		}
		else {
			m_fid = m_mnd_list[k + 0];
			m_offset = m_mnd_list[k + 1];
			m_num_bytes = m_mnd_list[k + 2];
			k += 3;
		}
		m_index_tk->Write_Stream_File(m_index_file_name, (m_traversal_state == ROOT_ENTER ? Standard : Append));
	}
	m_index_tk->Finalize_Stream_File(m_index_file_name);

	logging_str = H_FORMAT_TEXT("Generated OOC file.");
	m_pcw->LogMessage(logging_str, true);
}

/*****************************************************************************************************/

THREAD_FUNCTION ( m_key_data_list_thread_function ) {
	PointCloudIndexPopulateData *pcipd = THREAD_FUNCTION_DATA(PointCloudIndexPopulateData *);

#ifdef _M_IX86
	struct threadname_info {
		DWORD	type;		// must be 0x1000
		LPCSTR	name;		// pointer to name (in user addr space)
		DWORD	threadid;	// thread ID (-1=caller thread)
		DWORD	flags;		// reserved for future use, must be zero

		threadname_info (DWORD id, LPCSTR string) : type (0x1000), name (string), threadid (id), flags (0) {}
	};

	threadname_info	info ((DWORD)-1, (LPCSTR)"OOC Data Service");

	__try {
		RaiseException (0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info);
	}
	__except(EXCEPTION_CONTINUE_EXECUTION) {}
#endif

	while (pcipd->m_key_data_list_thread_exiting < 1) {

		HM_WAIT_SEMAPHORE(pcipd->m_key_data_list_semaphore);

		while (pcipd->m_key_data_list_thread_exiting < 1 &&
				pcipd->GetKeyDataList()->Count() > 0) {

			LOCK_MUTEX(pcipd->m_key_data_list_mutex);
			KeyDataPair *key_data_pair = pcipd->GetKeyDataList()->RemoveFirst();
			UNLOCK_MUTEX(pcipd->m_key_data_list_mutex);
			if (key_data_pair) {
				LoadNode(key_data_pair);
				pcipd->m_pcw->PleaseUpdate(true);
			}
		}
	}

	pcipd->m_key_data_list_thread_exiting--;
	return 0;
}

PointCloudStreamFileToolkit * PointCloudIndexPopulateData::GetNodeToolkit ( HThreadID id ) {
	PointCloudStreamFileToolkit *node_tk = 0;

	m_node_tk_hash->LookupItem(id, &node_tk);

	if (node_tk == 0) {
		node_tk = new PointCloudStreamFileToolkit(m_pcw);
		node_tk->SetOpcodeHandler(TKE_Shell, new TK_Point_Cloud_Node_Randomized());
		m_node_tk_hash->InsertItem(id, node_tk);
	}

	return node_tk;
}

char * PointCloudIndexPopulateData::GetWorkBuffer ( HThreadID id, unsigned int num_bytes ) {
	VCharArray * work_buffer = 0;

	m_work_buffer_hash->LookupItem(id, &work_buffer);

	if (work_buffer == 0) {
		work_buffer = new VCharArray();
		m_work_buffer_hash->InsertItem(id, work_buffer);
	}

	work_buffer->EnsureSize(num_bytes);

	return (char *)(*work_buffer);
}

void PointCloudIndexPopulateData::LockKeyDataList () {
	LOCK_MUTEX(m_key_data_list_mutex);
}

void PointCloudIndexPopulateData::UnlockKeyDataList () {
	UNLOCK_MUTEX(m_key_data_list_mutex);
	HM_RELEASE_SEMAPHORE(m_key_data_list_semaphore, 1);
}

FILE * PointCloudIndexPopulateData::GetFilePointer ( HThreadID id, unsigned int i ) {
	FILE **file_handles = 0;

	m_file_handle_hash->LookupItem(id, &file_handles);

	if (file_handles == 0) {
		file_handles = new FILE * [MAX_NUMBER_OPEN_FILES];
		for ( int j = 0 ; j < MAX_NUMBER_OPEN_FILES ; j++ )
			file_handles[j] = NULL;
		m_file_handle_hash->InsertItem(id, file_handles);
	}

	assert(i < MAX_NUMBER_OPEN_FILES);

	if (file_handles[i] == NULL) {
		wchar_t *master_node_file_name = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];	
		m_pcw->GetMasterNodeFileName(i, master_node_file_name);
		file_handles[i] = wfopen(master_node_file_name, L"rb");
		assert(file_handles[i] != NULL);
		delete [] master_node_file_name;
	}

	return file_handles[i];
}

#define THREADS_TO_USE 2
PointCloudIndexPopulateData::PointCloudIndexPopulateData ( PointCloudWorld * pcw_in ) {
	m_pcw = pcw_in;
	m_key_data_list = new KeyDataList();
	m_node_data_list = new NodeDataList();
	m_node_tk_hash = new ThreadToolkitHash();
	m_work_buffer_hash = new ThreadWorkBufferHash();
	m_file_handle_hash = new ThreadFileHandleHash();

	m_key_data_list_thread_exiting = 0;
	HM_CONSTRUCT_SEMAPHORE(m_key_data_list_semaphore, THREADS_TO_USE + 1111, 0);
	CREATE_MUTEX(m_key_data_list_mutex);

	m_key_data_list_thread = new HThreadHandle [THREADS_TO_USE];

	for ( int i = 0 ; i < THREADS_TO_USE ; i++ )
		CREATE_THREAD(m_key_data_list_thread[i], m_key_data_list_thread_function, (void *)this);
}

PointCloudIndexPopulateData::~PointCloudIndexPopulateData () {
	if (m_key_data_list) {
		// join thread
		m_key_data_list_thread_exiting = THREADS_TO_USE;
		HM_RELEASE_SEMAPHORE(m_key_data_list_semaphore, THREADS_TO_USE);

		while (m_key_data_list_thread_exiting > 0)
			MILLI_SECOND_SLEEP(10);

		for ( int i = 0 ; i < THREADS_TO_USE ; i++ )
			JOIN_THREAD(m_key_data_list_thread[i]);
		delete [] m_key_data_list_thread;
		m_key_data_list_thread = 0;

		DESTROY_MUTEX(m_key_data_list_mutex);
		HM_DESTRUCT_SEMAPHORE(m_key_data_list_semaphore);
		
		m_key_data_list->MapFunction(PopulateCleanup);
		
		m_key_data_list->DeleteItems();
		delete m_key_data_list;
	}

	if (m_node_data_list) {
		m_node_data_list->DeleteItems();
		delete m_node_data_list;
	}

	m_node_tk_hash->DeleteItems();
	delete m_node_tk_hash;

	m_work_buffer_hash->DeleteItems();
	delete m_work_buffer_hash;

	m_file_handle_hash->MapFunction(FileHandleCleanup);
	delete m_file_handle_hash;
}

void PointCloudIndexPopulateData::PopulateCleanup ( KeyDataPair * key_data_pair, void * user_data ) {
	HC_Commit_Proxy(key_data_pair->GetSegmentKey(), 0);
}

void PointCloudIndexPopulateData::FileHandleCleanup ( FILE ** file_handles, HThreadID id, void const * const user_data ) {
	if (file_handles == 0)
		return;

	for ( int i = 0 ; i < MAX_NUMBER_OPEN_FILES ; i++ ) {
		if (file_handles[i])
			fclose(file_handles[i]);
	}

	delete [] file_handles;
}

/*****************************************************************************************************/

TK_Point_Cloud_Index_Open_Segment::TK_Point_Cloud_Index_Open_Segment ( PointCloudWorld * pcw_in, PointCloudIndexNodeData * node_data_in ) {
	m_pcw = pcw_in;
	m_node_data = node_data_in;
	m_meta_stage = 0;
	m_meta_sub_stage = -1;
	m_node_dir_prefix_len = 0;
	m_node_dir_prefix = 0;
}

TK_Point_Cloud_Index_Open_Segment::~TK_Point_Cloud_Index_Open_Segment () {}

TK_Status TK_Point_Cloud_Index_Open_Segment::Read ( BStreamFileToolkit & tk ) alter {
	TK_Status status = TK_Normal;
	
	// we use m_meta_stage because TK_Open_Segment::Read uses m_stage and we need to call it
	switch (m_meta_stage) {
		case 0: {
			if ((status = TK_Open_Segment::Read(tk)) != TK_Normal)
				return status;
			
			m_meta_stage++;
		} nobreak;
		
		case 1: {
			if (m_stage != -1)
				assert(0);
				
			if ((status = GetData(tk, m_bbox, 6)) != TK_Normal)
				return status;
			
			m_meta_sub_stage = 0;
			m_meta_stage++;
		} nobreak;

		case 2: {
			if (streq(m_string, "root")) {
				switch (m_meta_sub_stage) {
					case 0: {
						int version = tk.GetVersion();
						unsigned int ooc_format_version;
						if ((status = GetData(tk, ooc_format_version)) != TK_Normal)
							return status;

						m_pcw->SetOOCFormatVersion(ooc_format_version);

						m_meta_sub_stage++;
					} nobreak;

					case 1: {
						if ((status = GetData(tk, m_node_dir_prefix_len)) != TK_Normal)
							return status;

						assert(m_node_dir_prefix == 0);
						m_node_dir_prefix = new char [m_node_dir_prefix_len];

						m_meta_sub_stage++;
					} nobreak;

					case 2: {
						if ((status = GetData(tk, m_node_dir_prefix, m_node_dir_prefix_len)) != TK_Normal)
							return status;

						H_UTF8 utf8;
						utf8.encodedText((utf8_char const *)m_node_dir_prefix);
						H_WCS wcs(utf8);

						m_pcw->SetNodeDirectoryPrefix(wcs.encodedText());

						delete [] m_node_dir_prefix;
						m_node_dir_prefix = 0;
						m_node_dir_prefix_len = 0;

						m_meta_sub_stage = -1;
					} break;

					default:
						status = TK_Error;
				}
			}

			m_meta_stage = -1;
		} break;

		default:
			status = TK_Error;
	}
	
	return status;
}

TK_Status TK_Point_Cloud_Index_Open_Segment::Execute ( BStreamFileToolkit & tk ) alter {
	TK_Status status = TK_Normal;

	HC_Open_Segment(m_string); {
		HC_Set_Bounding_Cuboid(m_bbox, m_bbox + 3);
		if (streq(m_string, "root")) {
			HC_Set_Rendering_Options("color interpolation = markers");
			HC_Set_Marker_Symbol(".");
			HC_Set_Marker_Size(0);
			HC_Set_Visibility("vertices = on");
			if (m_has_defined_callback == false) {
				HC_Define_Callback_Name("populate_node", reinterpret_cast<void (*)(...)>(PopulateNode));
				m_has_defined_callback = true;
			}
		}
	} // HC_Close_Segment(); -- segment will get closed by TKE_Close_Segment handler
	
	return status;
}

TK_Status TK_Point_Cloud_Index_Open_Segment::Write ( BStreamFileToolkit & tk ) alter {	
	TK_Status status = TK_Normal;
	
	if (m_skip_writing)
		return status;
	
	// we use m_meta_stage because TK_Open_Segment::Write uses m_stage and we need to call it
	switch (m_meta_stage) {
		case 0: {
			if ((status = TK_Open_Segment::Write(tk)) != TK_Normal)
				return status;
			
			m_meta_stage++;
		} nobreak;
		
		case 1: {
			if (m_stage != -1)
				assert(0);
				
			m_node_data->GetBBox(m_bbox);
			if ((status = PutData(tk, m_bbox, 6)) != TK_Normal)
				return status;
				
			m_meta_sub_stage = 0;
			m_meta_stage++;
		} nobreak;

		case 2: {
			if (streq(m_string, "root")) {
				switch (m_meta_sub_stage) {
					case 0: {
						// we'll store some version info in case we end up changing the format down the road
						if ((status = PutData(tk, OOC_FORMAT_VERSION)) != TK_Normal)
							return status;

						m_meta_sub_stage++;
					} nobreak;

					case 1: {
						wchar_t *node_dir_prefix = new wchar_t [m_pcw->GetNodeFileNameSize() + 1];
						m_pcw->GetNodeDirectoryPrefix(node_dir_prefix);

						H_UTF8 utf8(node_dir_prefix);
						m_node_dir_prefix_len = (int)strlen((char const *)utf8.encodedText()) + 1;
						assert(m_node_dir_prefix == 0);
						m_node_dir_prefix = new char [m_node_dir_prefix_len];
						strcpy(m_node_dir_prefix, (char const *)utf8.encodedText());

						delete [] node_dir_prefix;
						m_meta_sub_stage++;
					} nobreak;

					case 2: {
						if ((status = PutData(tk, m_node_dir_prefix_len)) != TK_Normal)
							return status;

						m_meta_sub_stage++;
					} nobreak;

					case 3: {
						if ((status = PutData(tk, m_node_dir_prefix, m_node_dir_prefix_len)) != TK_Normal)
							return status;

						delete [] m_node_dir_prefix;
						m_node_dir_prefix = 0;
						m_node_dir_prefix_len = 0;

						m_meta_sub_stage = -1;
					} break;

					default:
						status = TK_Error;
				}
			}

			m_meta_stage = -1;
		} break;

		default:
			status = TK_Error;
	}
	
	return status;
}

TK_Status TK_Point_Cloud_Index_Open_Segment::Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant ) alter {
	if (m_node_data == 0)
		return TK_Error;
	
	TK_Status status = TK_Normal;
	m_skip_writing = false;
	
	PointCloudStreamFileToolkit *pcsftk = static_cast<PointCloudStreamFileToolkit *>(&tk);
	if (pcsftk->GetCanPause() == false)
		m_skip_writing = true;
	else if (m_node_data->GetIsEnteringNode()) {
		Reset();
		
		switch (m_node_data->GetTreeTraversalState()) {
			case ROOT_ENTER: {
				set_segment("root");
			} break;
			
			case LEFT_BOTTOM_FRONT_ENTER: {
				set_segment("left_bottom_front");
			} break;
			
			case RIGHT_TOP_BACK_ENTER: {
				set_segment("right_top_back");
			} break;
			
			case OVERLAP_ENTER: {
				set_segment("overlap");
			} break;
			
			default:
				status = TK_Error;
		}
	}
	else // if (m_node_data->GetIsEnteringNode() == false)
		m_skip_writing = true;
	
	return status;
}

void TK_Point_Cloud_Index_Open_Segment::Reset () alter {
	m_meta_stage = 0;
	m_meta_sub_stage = -1;
	m_bbox[0] = m_bbox[1] = m_bbox[2] = m_bbox[3] = m_bbox[4] = m_bbox[5] = 0.0f;
	assert(m_node_dir_prefix == 0);
	
	TK_Open_Segment::Reset();
}

/*****************************************************************************************************/

TK_Point_Cloud_Index_Close_Segment::TK_Point_Cloud_Index_Close_Segment ( PointCloudWorld * pcw_in, PointCloudIndexNodeData * node_data_in ) {
	m_pcw = pcw_in;
	m_node_data = node_data_in;
	m_meta_stage = 0;
	m_meta_sub_stage = -1;
	m_fid = m_offset = m_num_bytes = 0;
}

TK_Point_Cloud_Index_Close_Segment::~TK_Point_Cloud_Index_Close_Segment () {}

TK_Status TK_Point_Cloud_Index_Close_Segment::Read ( BStreamFileToolkit & tk ) alter {
	TK_Status status = TK_Normal;

	switch (m_meta_stage) {
		case 0: {
			if ((status = TK_Close_Segment::Read(tk)) != TK_Normal)
				return status;

			m_meta_stage++;
			m_meta_sub_stage = 0;
		} nobreak;

		case 1: {
			switch (m_meta_sub_stage) {
				case 0: {
					if ((status = GetData(tk, m_fid)) != TK_Normal)
						return status;

					m_meta_sub_stage++;
				} nobreak;

				case 1: {
					if ((status = GetData(tk, m_offset)) != TK_Normal)
						return status;

					m_meta_sub_stage++;
				} nobreak;

				case 2: {
					if ((status = GetData(tk, m_num_bytes)) != TK_Normal)
						return status;

					m_meta_sub_stage = -1;
				} break;

				default:
					status = TK_Error;
			}

			m_meta_stage = -1;
		} break;

		default:
			status = TK_Error;
	}

	return status;
}

TK_Status TK_Point_Cloud_Index_Close_Segment::Execute ( BStreamFileToolkit & tk ) alter {
	if (m_pcw->GetLoadType() == LOAD_TYPE_IMMEDIATE) {
		// TODO: do this
	}
	else {
		NodeData *node_data = new NodeData(m_pcw);
		m_pcw->GetPopulateData()->GetNodeDataList()->AddLast(node_data);

		node_data->SetFileID(m_fid);
		node_data->SetOffset(m_offset);
		node_data->SetByteCount(m_num_bytes);

		HC_Set_Callback_With_Data("populate segment = populate_node", reinterpret_cast<void *>(node_data));
	}

	HC_Close_Segment();
	
	return TK_Close_Segment::Execute(tk);
}

TK_Status TK_Point_Cloud_Index_Close_Segment::Write ( BStreamFileToolkit & tk ) alter {	
	TK_Status status = TK_Normal;
	
	if (m_skip_writing)
		return status;
	
	// TK_Close_Segment::Write doesn't use m_stage currently, so we can use m_stage here, though this presents a couple issues
	//   - if that function ever does use m_stage, this function would need to change
	//   - it would employ a different design than that used by the other function which also needs to call it's base class write
	//     function, namely TK_Point_Cloud_Index_Open_Segment
	// To that end, we employ the same design as used in TK_Point_Cloud_Index_Open_Segment even though it isn't technically necessary
	switch (m_meta_stage) {
		case 0: {
			if ((status = TK_Close_Segment::Write(tk)) != TK_Normal)
				return status;
			
			m_meta_sub_stage = 0;
			m_meta_stage++;
		} nobreak;

		case 1: {
			switch (m_meta_sub_stage) {
				case 0: {
					m_node_data->GetMasterNodeData(m_fid, m_offset, m_num_bytes);

					if ((status = PutData(tk, m_fid)) != TK_Normal)
						return status;

					m_meta_sub_stage++;
				} nobreak;

				case 1: {
					if ((status = PutData(tk, m_offset)) != TK_Normal)
						return status;

					m_meta_sub_stage++;
				} nobreak;

				case 2: {
					if ((status = PutData(tk, m_num_bytes)) != TK_Normal)
						return status;

					m_meta_sub_stage = -1;
				} break;

				default:
					status = TK_Error;
			}
			
			m_meta_stage++;
		} nobreak;
		
		case 2: {
			PointCloudStreamFileToolkit *pcsftk = static_cast<PointCloudStreamFileToolkit *>(&tk);
			
			// if we aren't finalizing the stream file, we want to continue to add to it
			if (pcsftk->GetCanPause())
				status = TK_Revisit;
			
			m_meta_stage = -1;
		} break;
		
		default:
			status = TK_Error;
	}
	
	return status;
}

TK_Status TK_Point_Cloud_Index_Close_Segment::Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant ) alter {
	if (m_node_data == 0)
		return TK_Error;
	
	TK_Status status = TK_Normal;
	m_skip_writing = false;
	
	PointCloudStreamFileToolkit *pcsftk = static_cast<PointCloudStreamFileToolkit *>(&tk);
	if (pcsftk->GetCanPause() == false)
		m_skip_writing = true;
	else if (m_node_data->GetIsEnteringNode())
		status = TK_Revisit;
	else // if (m_node_data->GetIsEnteringNode() == false)
		Reset();
	
	return status;
}

void TK_Point_Cloud_Index_Close_Segment::Reset () alter {
	m_meta_stage = 0;
	m_meta_sub_stage = -1;
	m_fid = m_offset = m_num_bytes = 0;
	TK_Close_Segment::Reset();
}

/*****************************************************************************************************/

void PopulateNode ( HIC_Rendition const * nr, HC_KEY key ) {
	NodeData *node_data = reinterpret_cast<NodeData *>(const_cast<void *>(HIC_Show_Callback_Data(nr)));

	assert(node_data != 0);

	// this will either get deleted by the list (if doing an asynchronous read) or in a function call (if doing a synchronous read)
	KeyDataPair *key_data_pair = new KeyDataPair(node_data->GetWorld(), key, node_data);

	if (node_data->GetWorld()->GetLoadType() == LOAD_TYPE_SYNCHRONOUS)
		LoadNode(key_data_pair);	
	else {
		node_data->GetWorld()->GetPopulateData()->LockKeyDataList();
		node_data->GetWorld()->GetPopulateData()->GetKeyDataList()->AddLast(key_data_pair);
		node_data->GetWorld()->GetPopulateData()->UnlockKeyDataList();
	}
}

void LoadNode ( KeyDataPair * key_data_pair ) {
	char status[128];

	HC_Show_Key_Status (key_data_pair->GetSegmentKey(), status);

	if (!streq(status, "invalid")) {
		unsigned int num_bytes = key_data_pair->GetNodeData()->GetByteCount();
		char * node_file_buffer = key_data_pair->GetWorld()->GetPopulateData()->GetWorkBuffer(THREAD_ID(), num_bytes);

		FILE *fp = key_data_pair->GetWorld()->GetPopulateData()->GetFilePointer(THREAD_ID(), 
			key_data_pair->GetNodeData()->GetFileID());

		fseek(fp, key_data_pair->GetNodeData()->GetOffset(), SEEK_SET);
		size_t amount_read = fread(node_file_buffer, 1, num_bytes, fp);
		assert(amount_read == num_bytes);

		PointCloudStreamFileToolkit *tk = key_data_pair->GetWorld()->GetPopulateData()->GetNodeToolkit(THREAD_ID());
		tk->Restart();
		HC_Open_Segment_By_Key(key_data_pair->GetSegmentKey());
			TK_Status status = tk->ParseBuffer(node_file_buffer, num_bytes);
			assert(status == TK_Complete);
		HC_Close_Segment();
	}

	HC_Commit_Proxy(key_data_pair->GetSegmentKey(), 0);

	delete key_data_pair;
}
