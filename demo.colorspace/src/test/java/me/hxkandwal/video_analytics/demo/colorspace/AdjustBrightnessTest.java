package me.hxkandwal.video_analytics.demo.colorspace;

import org.junit.Test;

public class AdjustBrightnessTest {

	@Test
	public void testBrightness() throws Exception {
		AdjustBrightness.main(new String[] { System.getProperty("user.dir") + "/src/main/resources/assignment-1/fruit-plate-1.png", "10" });
		AdjustBrightness.main(new String[] { System.getProperty("user.dir") + "/src/main/resources/assignment-1/fruit-plate-2.png", "20" });
	}
	
}
