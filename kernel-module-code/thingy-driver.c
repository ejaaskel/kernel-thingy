// SPDX-License-Identifier: GPL-2.0-only
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/sysfs.h>

#define RANDOMSTRING_LEN 16

ssize_t randomstring_show(struct device *dev, struct device_attribute *dev_attr,
			  char *buf)
{
	char randomstring[RANDOMSTRING_LEN] = {0};
	struct i2c_client *client = dev_get_drvdata(dev);

	int recv_bytes = i2c_master_recv(client, randomstring,
					 RANDOMSTRING_LEN);

	if (recv_bytes >= 0) {
		/*
		 * i2c_master_recv fills randomstring with \xff if no character
		 * is received. Since received string is variable length, go
		 * through all the characters and convert to null terminator
		 */
		for (int i = 0; i < RANDOMSTRING_LEN; i++) {
			if (randomstring[i] == '\xff')
				randomstring[i] = '\0';
		}

		return sprintf(buf, "%s\n", randomstring);
	}

	pr_warn("Failed to read randomstring\n");

	return sprintf(buf, "%d\n", recv_bytes);
}

static DEVICE_ATTR_RO(randomstring);

static struct attribute *dev_attrs[] = {
	&dev_attr_randomstring.attr,
	NULL,
};

ATTRIBUTE_GROUPS(dev);

static const struct i2c_device_id thingy_id_table[] = {
	{ "thingy", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, thingy_id_table);

static int thingy_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	/*
	 * Copy i2c_client to drvdata so that it can be used when randomstring
	 * attribute is read
	 */
	dev_set_drvdata(&client->dev, client);

	return 0;
}

static struct i2c_driver thingy_i2c_driver = {
	.driver = {
		.name	= "thingy-driver",
		.dev_groups = dev_groups,
	},
	.probe		= thingy_probe,
	.id_table	= thingy_id_table,
};

module_i2c_driver(thingy_i2c_driver);

MODULE_LICENSE("GPL");
