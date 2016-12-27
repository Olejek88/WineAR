package ru.shtrm.ariant;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.Window;

public class MainActivity extends AppCompatActivity {
    private boolean splashShown = false;
    Bundle savedInstance = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        savedInstance = savedInstanceState;
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);

        if (savedInstanceState != null) {
            splashShown = savedInstanceState.getBoolean("splashShown");
        }

        if (!splashShown) {
            setContentView(R.layout.start_screen);

            Handler h = new Handler();
            h.postDelayed(new Runnable() {
                public void run() {
                    splashShown = true;
                    startImageTargets(savedInstance);
                }
            }, 3000);
        } else {
            startImageTargets(savedInstanceState);
        }

    }

    void startImageTargets(Bundle savedInstanceState) {
        Intent intent = new Intent(this, AboutScreen.class);
        intent.putExtra("ABOUT_TEXT_TITLE", "Чуть больше о вине");
        intent.putExtra("ABOUT_TEXT", "intro.html");
        startActivity(intent);

	}
}
