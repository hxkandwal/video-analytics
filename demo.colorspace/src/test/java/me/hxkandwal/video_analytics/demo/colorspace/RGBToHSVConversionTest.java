package me.hxkandwal.video_analytics.demo.colorspace;

import org.junit.Test;

public class RGBToHSVConversionTest {

	@Test
	public void testColorSpaceConversion() throws Exception {
		RGBToHSVConversion.main(new String[] { System.getProperty("user.dir") + "/src/main/resources/assignment-1/fruit-plate-1.png", "10" });
		RGBToHSVConversion.main(new String[] { System.getProperty("user.dir") + "/src/main/resources/assignment-1/fruit-plate-2.png", "20" });
	}

}
