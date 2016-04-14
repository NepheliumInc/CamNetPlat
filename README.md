# CamNetPlat

Person re-identification across CCTV networks with disjoint camera fields of view is a highly challenging task due to different characteristics in camera nodes, context based illumination conditions and uncontrolled pose variations of humans across camera views which heavily increases the complexity of the problem. Furthermore when scaling for increased number of cameras being monitored, this becomes a high resource consuming problem which render complex appearance based feature detectors somewhat difficult to manage in the real time. The proposed solution, handles multiple video streams, identifies blobs, determines whether they are human and will profile and track them. We further implemented a scalable methodology for feature detection involving a simple but fast feature vector based on color moments combined with logical filtering and management of human profiles entering a camera network along with the optimization of processing using parallelized algorithms which runs on CUDA enabled Graphics Processing Unit. The introduced feature vector together with profile management provides a robust yet efficient mechanism to re-identify humans. The integration of cuda provides the ability to scale this platform to a greater number of video streams without incurring a significant performance penalty.

youtube link for demo : 
<a href="http://www.youtube.com/watch?feature=player_embedded&v=t4Uz9LWimzA
" target="_blank"><img src="http://img.youtube.com/vi/t4Uz9LWimzA/0.jpg" 
alt="Demo Video of CamnetPlat - Nephelium" width="560" height="315" border="10" /></a> 
