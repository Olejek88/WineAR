package ru.shtrm.ariant.ImageTargets;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

import com.vuforia.Vuforia;


/** The renderer class for the ImageTargets sample. */
public class ImageTargetsRenderer implements GLSurfaceView.Renderer
{
    public boolean mIsActive = false;
    
    /** Reference to main activity **/
    public ImageTargets mActivity;
    
    
    /** Native function for initializing the renderer. */
    public native void initRendering();
    
    
    /** Native function to update the renderer. */
    public native void updateRendering(int width, int height);


    /** Native method for updating rendering primitive */
    public native void updateRenderingPrimitives();


    /** Called when the surface is created or recreated. */
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        // Call native function to initialize rendering:
        initRendering();
        
        // Call Vuforia function to (re)initialize rendering after first use
        // or after OpenGL ES context was lost (e.g. after onPause/onResume):
        Vuforia.onSurfaceCreated();
    }
    
    
    /** Called when the surface changed size. */
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        // Call native function to update rendering when render surface
        // parameters have changed:
        updateRendering(width, height);
        
        // Call Vuforia function to handle render surface size changes:
        Vuforia.onSurfaceChanged(width, height);

        updateRenderingPrimitives();
    }
    

    /** The native render function. */
    public native void renderFrame();
    
    
    /** Called to draw the current frame. */
    public void onDrawFrame(GL10 gl)
    {
        if (!mIsActive)
            return;
        
        // Update render view (projection matrix and viewport) if needed:
        mActivity.updateRenderView();
        
        // Call our native function to render content
        renderFrame();
    }
}
